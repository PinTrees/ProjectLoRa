#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CSprite.h"



CPanelUI::CPanelUI()
	: CUI(false)
	, mpTexture(nullptr)
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
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	if (mpTexture)
	{
		mpTexture->Render(dc, vPos, vScale);
	}

	CUI::Render(dc);
	CUI::RenderChild(dc);
}

void CPanelUI::MouseOn()
{
	if (mFixedPos || (mFixedPos_x && mFixedPos_y))
		return;

	if (IsLbtnDown())
	{
		Vect2 vDiff = (MOUSE_POS - mvDragStartPos);
		Vect2 vCurPos = GetPos();

		if (mFixedPos_x && !mFixedPos_y)
		{
			vCurPos.y += vDiff.y;
		}
		else if (!mFixedPos_x && mFixedPos_y)
		{
			vCurPos.x += vDiff.x;
		}
		else if (!mFixedPos_x && !mFixedPos_y)
		{
			vCurPos += vDiff;
		}

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
