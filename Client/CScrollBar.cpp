#include "pch.h"
#include "CScrollBar.h"

#include "CKeyMgr.h"

#include "CScrollView.h"
#include "CTexture.h"



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


void CScrollBar::Render(HDC dc)
{
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vSize = GetScale();

	if (mpBufferTexture)
	{
		// AlpaBlend Option Setting
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = GetAlpha();

		AlphaBlend(dc
			, (int)(vPos.x - vSize.x * 0.5f)
			, (int)(vPos.y - vSize.y * 0.5f)
			, (int)vSize.x
			, (int)vSize.y
			, mpBufferTexture->GetDC()
			, 0, 0
			, (int)mpBufferTexture->Width()
			, (int)mpBufferTexture->Heigth(), bf);
	}

	CUI::Render(dc);
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
