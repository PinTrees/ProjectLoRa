#include "pch.h"
#include "CUI.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "SelectGDI.h"
#include "CScene.h"
#include "CTexture.h"

CUI::CUI(bool cameraAffected)
	:
	_vecChildUI{},
	p_parentUI(nullptr),
	_finalPos{},
	_cameraAffected(cameraAffected),
	_onMouseCheck(false),
	_lbtnDown(false)
	, mpTexture(nullptr)
	, mText{}
{

}

CUI::CUI(const CUI& origin)
	:
	CObject(origin),
	p_parentUI(nullptr),
	_cameraAffected(origin._cameraAffected),
	_onMouseCheck(false),
	_lbtnDown(false)
	, mpTexture(nullptr)
	, mText{}
{
	for (size_t i = 0; i < origin._vecChildUI.size(); ++i)
	{
		AddChild(origin._vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(_vecChildUI);
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
	_finalPos = GetPos(); // 부모 좌표를 finalPos로 인식

	if (GetParentUI())
	{
		Vec2 parentPos = GetParentUI()->GetFinalPos();
		_finalPos += parentPos;
	}

	// UI Mouse체크
	OnMouseCheck();

	FinalUpdateChild();
}

void CUI::OnMouseCheck()
{
	Vec2 mousePos = MOUSE_POS;
	Vec2 uiScale = GetScale();

	if (_cameraAffected)
	{
		CCamera::GetI()->GetRealPos(mousePos);
	}

	if (_finalPos.x <= mousePos.x && mousePos.x <= _finalPos.x + uiScale.x &&
		_finalPos.y <= mousePos.y && mousePos.y <= _finalPos.y + uiScale.y)
	{
		_onMouseCheck = true;
	}
	else
	{
		_onMouseCheck = false;
	}
}

void CUI::Render(HDC dc)
{
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();

	if (_cameraAffected)
	{
		pos = CCamera::GetI()->GetRenderPos(pos);
	}

	if (_lbtnDown)
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

	if (mpTexture)
	{
		Vec2 vSize = mpTexture->GetSize();

		float fWidth = (float)mpTexture->Width();
		float fHeight = (float)mpTexture->Heigth();

		TransparentBlt(dc
			, (int)(pos.x + mvContentOffset.x)
			, (int)(pos.y + mvContentOffset.y)
			, (int)vSize.x, (int)vSize.y
			, mpTexture->GetDC()
			, 0, 0
			, (int)fWidth, (int)fHeight
			, RGB(255, 0, 255));
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
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->Update();
	}
}

void CUI::FinalUpdateChild()
{
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::RenderChild(HDC dc)
{
	for (size_t i = 0; i < _vecChildUI.size(); ++i)
	{
		_vecChildUI[i]->Render(dc);
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
	// 밖에서 누르고 안에서 땟을 때도 인식이 된다.

}

void CUI::MouseLbtnClick()
{

}
