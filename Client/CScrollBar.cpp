#include "pch.h"
#include "CScrollBar.h"

#include "CKeyMgr.h"

#include "CScrollView.h"


CScrollBar::CScrollBar()
	: CUI(false)
	, mAxis(AXIS::VERTICAL)
	, mbDrag(false)
{
	SetOriginalMouseCheck(true);
}

CScrollBar::~CScrollBar()
{
}



void CScrollBar::Update()
{
	CUI::Update();

	if (IsLbtnDown())
	{
		Vect2 vDiff = (MOUSE_POS - mvDragStartPos);
		Vect2 vCurPos = GetPos();

		if (AXIS::VERTICAL == mAxis)
		{
			vCurPos.y += vDiff.y;
			mScrollView->SetVerticalScroll();
		}
		else if (AXIS::HORIZONTAL == mAxis)
		{
			vCurPos.x += vDiff.x;
		}

		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
	}
}


void CScrollBar::Render(HDC _dc)
{
	CUI::Render(_dc);
}



void CScrollBar::MouseOn()
{
	
}


void CScrollBar::MouseLbtnDown()
{
	mbDrag = true;
	mvDragStartPos = MOUSE_POS;
}

void CScrollBar::MouseLbtnUp()
{
	mbDrag = false;
}
