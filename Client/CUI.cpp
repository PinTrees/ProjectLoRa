#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"


CUI::CUI(bool cameraAffected)
	: mVecChildUI{}
	, mpParentUI(nullptr)
	, mvFinalPos{}
	, mCameraAffected(cameraAffected)
	, mOnMouseCheck(false)
{
}

CUI::CUI(const CUI& origin)
	: CObject(origin)
	, mpParentUI(nullptr)
	, mCameraAffected(origin.mCameraAffected)
	, mOnMouseCheck(false)
	, mLbtnDown(false)
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
		mvFinalPos += parentPos;
	}

	// UI Mouse체크
	OnMouseCheck();

	FinalUpdateChild();
}

void CUI::OnMouseCheck()
{
	Vect2 mousePos = MOUSE_POS;
	Vect2 uiScale = GetScale();

	if (mCameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

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

void CUI::Render(HDC dc)
{
	if (GetAnimator())
	{
		GetAnimator()->GetCurAnimation()->RenderUI(this, dc);
		return;
	}

	Vect2 vPos = GetFinalPos();
	Vect2 vScale = GetScale();

	if (mCameraAffected)
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
	}

	if (mLbtnDown)
	{
		SelectGDI p(dc, PEN_TYPE::GREEN);
	}

	if(nullptr == mpTexture)
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
	else
	{
		float fWidth = (float)mpTexture->Width();
		float fHeight = (float)mpTexture->Heigth();

		TransparentBlt(dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)vScale.x
			, (int)vScale.y
			, mpTexture->GetDC()
			, 0, 0
			, (int)fWidth, (int)fHeight
			, RGB(255, 0, 255));
	}

	// child render
	RenderChild(dc);
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