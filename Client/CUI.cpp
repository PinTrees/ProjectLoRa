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

	// �θ��� finalUpdateȣ�� �ؾ��Ѵ�.
	// UI�� �ִϸ��̼� ���� ���� �ֱ� ������
	CObject::FinalUpdate();

	// UI�� ������ǥ�� ���Ѵ�.
	mvFinalPos = GetPos(); // �θ� ��ǥ�� finalPos�� �ν�

	if (GetParentUI())
	{
		Vect2 parentPos = GetParentUI()->GetFinalPos();
		mvFinalPos += parentPos + mvOffset;
	}

	// UI Mouseüũ
	OnMouseCheck();

	// mDeleteChildUI�� �߰��� ��ü���� mVecChildUI���� ����
	for (int i = 0; i < mDeleteChildUI.size(); ++i)
	{
		// �ش� ��ü�� ���Ϳ��� ã�Ƽ� ����
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

	// �θ� UI���� �ڽ� UI ���콺��ǥ ���� �������� ������ ���
	if (mpParentUI && IsFixedChildMouseCheck() && !mOriginalMouseCheck)
	{
		// ������ �ɸ� �ֻ��� �θ� ȹ��
		CUI* pFixedParentUI = GetFixedChildMouseCheckParent();
		// ������ �ɸ� �ֻ��� �θ�UI�� ������ ȹ��
		Vect2 vParentFinalPos = pFixedParentUI->GetFinalPos();
		Vect2 vParentUiScale = pFixedParentUI->GetScale();

		// ���ѵ� ���콺 ���� ��ǥ�� Ŭ���� ���
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
	// �������� ��ǥ ���� ����
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
	// �ۿ��� ������ �ȿ��� ���� ���� �ν��� �ȴ�.

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


// ��� �θ� UI�� �� ��ǥ���� ������ ������ UI�� �ִ��� Ȯ���մϴ�.
bool CUI::IsFixedChildMouseCheck()
{
	vector<CUI*> vecParentUI;
	CUI* parentUI = this;

	// ��� �θ� UI�� ȹ��
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

// ��� �θ� UI�� �� ��ǥ���� ������ ������ UI�� ��ȯ�մϴ�.
// �ɼ��� 2�� �����Ǿ��ִٸ� �� ���� UI�� ��ȯ�մϴ�.
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

