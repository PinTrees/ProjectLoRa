#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "UIMgr.h"



CUI::CUI(bool cameraAffected)
	: mVecChildUI{}
	, mpParentUI(nullptr)
	, mvFinalPos{}
	, mCameraAffected(cameraAffected)
	, mOnMouseCheck(false)
	, mvOffset(Vect2::zero)
	, mFixedChildMouseCheck(false)
	, mOriginalMouseCheck(false)
	, mbRaycastTarget(true)
{
}

CUI::CUI(const CUI& origin)
	: CObject(origin)
	, mpParentUI(nullptr)
	, mCameraAffected(origin.mCameraAffected)
	, mOnMouseCheck(false)
	, mLbtnDown(false)
	, mFixedChildMouseCheck(origin.mFixedChildMouseCheck)
	, mOriginalMouseCheck(origin.mOriginalMouseCheck)
	, mbRaycastTarget(origin.mbRaycastTarget)
{
	for (size_t i = 0; i < origin.mVecChildUI.size(); ++i)
	{
		AddChild(origin.mVecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(mVecChildUI);
}




void CUI::Update() 
{
	// child update
	UpdateChild();
}

void CUI::FinalUpdate()
{
	if (GetAnimator())
		GetAnimator()->Update();

	// 부모의 finalUpdate호출 해야한다.
	// UI가 애니매이션 가질 수도 있기 때문에
	CObject::FinalUpdate();

	// UI의 최종좌표를 구한다.
	mvFinalPos = GetPos(); // 부모 좌표를 finalPos로 인식

	if (GetParentUI())
	{
		Vect2 parentPos = GetParentUI()->GetFinalPos();
		mvFinalPos += parentPos + mvOffset;
	}

	// UI Mouse체크
	OnMouseCheck();

	// mDeleteChildUI에 추가된 객체들을 mVecChildUI에서 삭제
	for (int i = 0; i < mDeleteChildUI.size(); ++i)
	{
		// 해당 객체를 벡터에서 찾아서 삭제
		auto iter = std::find(mVecChildUI.begin(), mVecChildUI.end(), mDeleteChildUI[i]);
		if (iter != mVecChildUI.end()) {
			mVecChildUI.erase(iter);
		}
	}
	mDeleteChildUI.clear();

	FinalUpdateChild();
}


void CUI::OnMouseCheck()
{
	if (!mbRaycastTarget)
		return;

	Vect2 mousePos = MOUSE_POS;
	Vect2 uiScale = GetScale();

	if (mCameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

	// 부모 UI들중 자식 UI 마우스좌표 범위 제한으로 설정된 경우
	if (mpParentUI && IsFixedChildMouseCheck() && !mOriginalMouseCheck)
	{
		// 제한이 걸린 최상위 부모를 획득
		CUI* pFixedParentUI = GetFixedChildMouseCheckParent();
		// 제한이 걸린 최상위 부모UI의 정보를 획득
		Vect2 vParentFinalPos = pFixedParentUI->GetFinalPos();
		Vect2 vParentUiScale = pFixedParentUI->GetScale();

		// 제한된 마우스 범위 좌표로 클릭을 계산
		if (vParentFinalPos.x - vParentUiScale.x * 0.5f <= mousePos.x && mousePos.x <= vParentFinalPos.x + vParentUiScale.x * 0.5f &&
			vParentFinalPos.y - vParentUiScale.y * 0.5f <= mousePos.y && mousePos.y <= vParentFinalPos.y + vParentUiScale.y * 0.5f &&
			mvFinalPos.x - uiScale.x * 0.5f <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x * 0.5f &&
			mvFinalPos.y - uiScale.y * 0.5f <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y * 0.5f)
		{
			mOnMouseCheck = true;
		}
		else
		{
			mOnMouseCheck = false;
		}
	}
	// 오리지널 좌표 범위 연산
	else
	{
		if (mvFinalPos.x - uiScale.x * 0.5f <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x * 0.5f &&
			mvFinalPos.y - uiScale.y * 0.5f <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y * 0.5f)
		{
			mOnMouseCheck = true;
		}
		else
		{
			mOnMouseCheck = false;
		}
	}
}


void CUI::Render(HDC dc)
{
	if (GetAnimator())
	{
		GetAnimator()->GetCurAnimation()->RenderUI(this, dc);
		return;
	}
	
	SelectGDI b(dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(dc, PEN_TYPE::RED);

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	if (DEBUG)
	{
		Rectangle
		(
			dc,
			int(vPos.x - vScale.x * 0.5f),
			int(vPos.y - vScale.y * 0.5f),
			int(vPos.x + vScale.x * 0.5f),
			int(vPos.y + vScale.y * 0.5f)
		);
	}
}

void CUI::UpdateChild()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->Update();
	}
}

void CUI::FinalUpdateChild()
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->FinalUpdate();
	}
}

void CUI::RenderChild(HDC dc)
{
	for (size_t i = 0; i < mVecChildUI.size(); ++i)
	{
		if (mVecChildUI[i]->IsVisible())
			mVecChildUI[i]->Render(dc);
	}
}




void CUI::OnDestroy()
{
}

void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{
	// 밖에서 누르고 안에서 땟을 때도 인식이 된다.

}

void CUI::MouseLbtnClick()
{

}


void CUI::SetDead()
{
	CObject::SetDead();
	for (int i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->SetDead();
	}
}


void CUI::AddChild(CUI* ui)
{
	mVecChildUI.push_back(ui);
	ui->mpParentUI = this;
}

void CUI::DeleteChild(CUI* ui)
{
	mDeleteChildUI.push_back(ui);
}


void CUI::SetTopChild(CUI* ui)
{
	if (nullptr == ui)
		return;

	vector<CUI*>::iterator iter = mVecChildUI.begin();

	for (; iter != mVecChildUI.end(); ++iter)
	{
		if (ui == *iter)
			break;
	}

	mVecChildUI.erase(iter);
	mVecChildUI.push_back(ui);
}




CUI* CUI::GetFindChild(CUI* parentUI, const wstring& childUI)
{
	for (UINT i = 0; i < parentUI->GetChild().size(); ++i)
	{
		if (parentUI->GetChild()[i]->GetName() == childUI)
		{
			if (parentUI->GetChild()[i] == nullptr)
				assert(nullptr);

			return parentUI->GetChild()[i];
		}
	}

	return nullptr;
}


// 모든 부모 UI들 중 좌표범위 제한이 설정된 UI가 있는지 확인합니다.
bool CUI::IsFixedChildMouseCheck()
{
	vector<CUI*> vecParentUI;
	CUI* parentUI = this;

	// 모든 부모 UI를 획득
	while (parentUI)
	{
		vecParentUI.push_back(parentUI);
		parentUI = parentUI->mpParentUI;
	}

	bool result = false;
	for (int i = 0; i < vecParentUI.size(); ++i)
	{
		if (vecParentUI[i]->mFixedChildMouseCheck)
		{
			result = true;
			break;
		}
	}

	vecParentUI.clear();
	return result;
}

// 모든 부모 UI들 중 좌표범위 제한이 설정된 UI를 반환합니다.
// 옵션이 2중 설정되어있다면 최 하위 UI를 반환합니다.
CUI* CUI::GetFixedChildMouseCheckParent()
{
	vector<CUI*> vecParentUI;
	CUI* parentUI = this;

	while (parentUI)
	{
		vecParentUI.push_back(parentUI);
		parentUI = parentUI->mpParentUI;
	}

	parentUI = nullptr;

	for (int i = 0; i < vecParentUI.size(); ++i)
	{
		if (vecParentUI[i]->mFixedChildMouseCheck)
		{
			parentUI = vecParentUI[i];
		}
	}

	vecParentUI.clear();
	return parentUI;
}








bool CUI::IsAligmentLeft(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::BOTTOM_LEFT
		|| aligment == ALIGNMENT::CENTER_LEFT
		|| aligment == ALIGNMENT::TOP_LEFT)
		return true;
	else return false;
}

bool CUI::IsAligmentRight(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::BOTTOM_RIGHT
		|| aligment == ALIGNMENT::CENTER_RIGHT
		|| aligment == ALIGNMENT::TOP_RIGHT)
		return true;
	else return false;
}

bool CUI::IsAligmentCenter_Ver(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::TOP_CENTER
		|| aligment == ALIGNMENT::TOP_LEFT
		|| aligment == ALIGNMENT::TOP_RIGHT)
		return true;
	else return false;
}

bool CUI::IsAligmentCenter_Hor(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::CENTER
		|| aligment == ALIGNMENT::CENTER_LEFT
		|| aligment == ALIGNMENT::CENTER_RIGHT)
		return true;
	else return false;
}

bool CUI::IsAligmentCenter(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::CENTER
		|| aligment == ALIGNMENT::CENTER_LEFT
		|| aligment == ALIGNMENT::CENTER_RIGHT
		|| aligment == ALIGNMENT::TOP_CENTER
		|| aligment == ALIGNMENT::BOTTOM_CENTER)
		return true;
	else return false;
}

bool CUI::IsAligmentTop(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::TOP_CENTER
		|| aligment == ALIGNMENT::TOP_LEFT
		|| aligment == ALIGNMENT::TOP_RIGHT)
		return true;
	else return false;
}



bool CUI::IsAligmentBottom(ALIGNMENT aligment)
{
	if (aligment == ALIGNMENT::BOTTOM_CENTER
		|| aligment == ALIGNMENT::BOTTOM_LEFT
		|| aligment == ALIGNMENT::BOTTOM_RIGHT)
		return true;
	else return false;
}

