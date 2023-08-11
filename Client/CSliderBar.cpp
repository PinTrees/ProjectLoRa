#include "pch.h"
#include "CSliderBar.h"

#include "CKeyMgr.h"

#include "CTexture.h"

CSliderBar::CSliderBar()
	: CUI(false)
	, mpOwner(nullptr)
	, mpTex(nullptr)
	, mpFunc(nullptr)
	, mParam(0)
{
	SetOriginalMouseCheck(true);
}

CSliderBar::~CSliderBar()
{
}


void CSliderBar::Update()
{
	CUI::Update();

	if (IsLbtnDown())
	{
		Vect2 vDiff = (MOUSE_POS - mvDragStartPos);
		Vect2 vCurPos = GetPos();

		vCurPos.x += vDiff.x;

		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
	}
}

void CSliderBar::Render(HDC dc)
{
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vSize = GetScale();

	if (mpTex)
	{
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
			, mpTex->GetDC()
			, 0, 0
			, (int)mpTex->Width()
			, (int)mpTex->Heigth(), bf);
	}

	CUI::Render(dc);
}

void CSliderBar::MouseOn()
{
}

void CSliderBar::MouseLbtnDown()
{
	mvDragStartPos = MOUSE_POS;

	if (nullptr != mpFunc)
	{
		mpFunc(mParam);
	}
}

void CSliderBar::MouseLbtnUp()
{
}
