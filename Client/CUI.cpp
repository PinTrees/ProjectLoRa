#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"
<<<<<<< Updated upstream
#include "CFont.h"
#include "CTexture.h"

=======

#include "CTexture.h"


>>>>>>> Stashed changes
CUI::CUI(bool cameraAffected)
	: mVecChildUI{}
	, mpParentUI(nullptr)
	, mvFinalPos{}
	, mCameraAffected(cameraAffected)
	, mOnMouseCheck(false)
<<<<<<< Updated upstream
	, mFont(nullptr)
	, mColor(0)
	, mLbtnDown(false)
	, mpTexture(nullptr)
=======
>>>>>>> Stashed changes
{

}

CUI::CUI(const CUI& origin)
	: CObject(origin)
	, mpParentUI(nullptr)
	, mCameraAffected(origin.mCameraAffected)
	, mOnMouseCheck(false)
	, mLbtnDown(false)
<<<<<<< Updated upstream
	, mFont(nullptr)
	, mColor(0)
	, mpTexture(nullptr)
=======
>>>>>>> Stashed changes
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
	// 부모의 finalUpdate호출 해야한다.
	// UI가 애니매이션 가질 수도 있기 때문에
	CObject::FinalUpdate();

	// UI의 최종좌표를 구한다.
	mvFinalPos = GetPos(); // 부모 좌표를 finalPos로 인식

	if (GetParentUI())
	{
<<<<<<< Updated upstream
		Vec2 parentPos = GetParentUI()->GetFinalPos();
=======
		Vect2 parentPos = GetParentUI()->GetFinalPos();
>>>>>>> Stashed changes
		mvFinalPos += parentPos;
	}

	// UI Mouse체크
	OnMouseCheck();

	FinalUpdateChild();
}

void CUI::OnMouseCheck()
{
<<<<<<< Updated upstream
	Vec2 mousePos = MOUSE_POS;
	Vec2 uiScale = GetScale();
=======
	Vect2 mousePos = MOUSE_POS;
	Vect2 uiScale = GetScale();
>>>>>>> Stashed changes

	if (mCameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

<<<<<<< Updated upstream
	if (mvFinalPos.x <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x &&
		mvFinalPos.y <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y)
=======
	if (mvFinalPos.x - uiScale.x * 0.5f <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x * 0.5f &&
		mvFinalPos.y - uiScale.y * 0.5f <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y * 0.5f)
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();

	if (mCameraAffected)
	{
		pos = CCamera::GetI()->GetRenderPos(pos);
=======
	Vect2 vPos = GetFinalPos();
	Vect2 vScale = GetScale();

	if (mCameraAffected)
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
>>>>>>> Stashed changes
	}

	if (mLbtnDown)
	{
		SelectGDI p(dc, PEN_TYPE::GREEN);
<<<<<<< Updated upstream
		Rectangle
		(
			dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
=======
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
>>>>>>> Stashed changes
		);
	}
	else
	{
<<<<<<< Updated upstream
		Rectangle
		(
			dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}

	if (mpTexture != nullptr)
	{
		Vec2 size = mpTexture->GetSize();

		float fWidth = mpTexture->Width();
		float fHeight = mpTexture->Heigth();

		TransparentBlt(dc
			, (int)(pos.x + mvContentOffset.x)
			, (int)(pos.y + mvContentOffset.y)
			, (int)size.x , (int)size.y
=======
		float fWidth = (float)mpTexture->Width();
		float fHeight = (float)mpTexture->Heigth();

		TransparentBlt(dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)vScale.x
			, (int)vScale.y
>>>>>>> Stashed changes
			, mpTexture->GetDC()
			, 0, 0
			, (int)fWidth, (int)fHeight
			, RGB(255, 0, 255));
	}

<<<<<<< Updated upstream
	if (mFont != nullptr)
	{
		mFont->PrintWord(pos + mvContentOffset);
	}

=======
>>>>>>> Stashed changes
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
		mVecChildUI[i]->Render(dc);
	}
}

<<<<<<< Updated upstream
=======



void CUI::OnDestroy()
{
}

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======

void CUI::SetDead()
{
	CObject::SetDead();
	for (int i = 0; i < mVecChildUI.size(); ++i)
	{
		mVecChildUI[i]->SetDead();
	}
}

>>>>>>> Stashed changes
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