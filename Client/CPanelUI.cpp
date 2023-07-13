#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false)
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
	if (IsLbtnDown())
	{
<<<<<<< Updated upstream
	 	Vec2 vDiff =(MOUSE_POS - mvDragStartPos);


		Vec2 vCurPos = GetPos();
=======
	 	Vect2 vDiff = (MOUSE_POS - mvDragStartPos);

		Vect2 vCurPos = GetPos();
>>>>>>> Stashed changes
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
