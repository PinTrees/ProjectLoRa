#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CSprite.h"



CPanelUI::CPanelUI()
	: CUI(false)
	, mpSprite(nullptr)
	, mFixedPos(true)
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::Update()
{
	CUI::Update();
}

void CPanelUI::Render(HDC dc)
{
	CUI::Render(dc);

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	if (mpSprite)
	{
		mpSprite->Render(dc, vPos, vScale);
	}

	CUI::RenderChild(dc);
}

void CPanelUI::MouseOn()
{
	if (mFixedPos)
		return;

	if (IsLbtnDown())
	{
	 	Vect2 vDiff = (MOUSE_POS - mvDragStartPos);

		Vect2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
	}
}


void CPanelUI::MouseLbtnDown()
{
	mvDragStartPos = MOUSE_POS;
}


void CPanelUI::MouseLbtnUp()
{

}
