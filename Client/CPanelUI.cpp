#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false)
	, mFixedPos_x(true)
	, mFixedPos_y(true)
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::Update()
{
	CUI::Update();
}

void CPanelUI::Render(HDC _dc)
{
	CUI::Render(_dc);
}

void CPanelUI::MouseOn()
{
	if (mFixedPos_x && mFixedPos_y)
		return;

	if (mFixedPos_x &&!mFixedPos_y && IsLbtnDown())
	{
		Vect2 vDiff = (MOUSE_POS - mvDragStartPos);

		Vect2 vCurPos = GetPos();
		vCurPos.y += vDiff.y;
		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
		return;
	}

	if (!mFixedPos_x && !mFixedPos_y && IsLbtnDown())
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
