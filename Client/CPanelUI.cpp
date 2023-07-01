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
	 	Vec2 vDiff =(MOUSE_POS - mvDragStartPos);


		Vec2 vCurPos = GetPos();
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
