#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false)
	, mbFixedPos(false)
{

}

CPanelUI::~CPanelUI()
{

}


void CPanelUI::Update()
{
}

void CPanelUI::Render(HDC _dc)
{
	CUI::Render(_dc);
}

void CPanelUI::MouseOn()
{
	CUI::MouseOn();
<<<<<<< Updated upstream
	
	if (mbFixedPos && IsLbtnDown())
=======

	if (IsLbtnDown())
>>>>>>> Stashed changes
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
