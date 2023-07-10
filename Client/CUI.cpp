#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"

CUI::CUI(bool cameraAffected)
	: mVecChildUI{}
	, mpParentUI(nullptr)
	, mvFinalPos{}
	, mCameraAffected(cameraAffected)
	, mOnMouseCheck(false)
	, mText(L"")
{

}

CUI::CUI(const CUI& origin)
	: CObject(origin)
	, mpParentUI(nullptr)
	, mCameraAffected(origin.mCameraAffected)
	, mOnMouseCheck(false)
	, mLbtnDown(false)
	, mText(origin.mText)
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
	// �θ��� finalUpdateȣ�� �ؾ��Ѵ�.
	// UI�� �ִϸ��̼� ���� ���� �ֱ� ������
	CObject::FinalUpdate();

	// UI�� ������ǥ�� ���Ѵ�.
	mvFinalPos = GetPos(); // �θ� ��ǥ�� finalPos�� �ν�

	if (GetParentUI())
	{
		Vec2 parentPos = GetParentUI()->GetFinalPos();
		mvFinalPos += parentPos;
	}

	// UI Mouseüũ
	OnMouseCheck();

	FinalUpdateChild();
}

void CUI::OnMouseCheck()
{
	Vec2 mousePos = MOUSE_POS;
	Vec2 uiScale = GetScale();

	if (mCameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

	if (mvFinalPos.x <= mousePos.x && mousePos.x <= mvFinalPos.x + uiScale.x &&
		mvFinalPos.y <= mousePos.y && mousePos.y <= mvFinalPos.y + uiScale.y)
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
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();

	if (mCameraAffected)
	{
		pos = CCamera::GetI()->GetRenderPos(pos);
	}

	if (mLbtnDown)
	{
		SelectGDI p(dc, PEN_TYPE::GREEN);
		Rectangle
		(
			dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}
	else
	{
		Rectangle
		(
			dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}

	if (mText != L"")
	{
		TextOut(dc, (int)(pos.x + mvContentOffset.x), (int)(pos.y + mvContentOffset.y), mText.c_str(), mText.size());
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
		mVecChildUI[i]->Render(dc);
	}
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