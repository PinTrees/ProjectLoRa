#include "pch.h"
#include "CSliderBar.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CSlider.h"


CSliderBar::CSliderBar()
	: CUI(false)
	, mbDrag(false)
{
	SetOriginalMouseCheck(true);

	SetScale(Vect2(50.f, 20.f));
	mpTex = CResMgr::GetI()->LoadTexture(L"SliderBar", L"texture\\ui\\slider\\bar.bmp");
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
		mpOwner->SetHorSliderValue();

		SetPos(vCurPos);
		mvDragStartPos = MOUSE_POS;
	}
}

void CSliderBar::Render(HDC dc)
{
	// Set Render Pos and Scale
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vSize = GetScale();

	// AlpaBlend Option Setting
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = GetAlpha();

	// Default Image Render Mode 
	if (mpTex)
	{
		AlphaBlend(dc
			, (int)(vPos.x - vSize.x * 0.5f)
			, (int)(vPos.y - vSize.y * 0.5f)
			, (int)vSize.x
			, (int)vSize.y
			, mpTex->GetDC()
			, 0, 0
			, (int)mpTex->Width()
			, (int)mpTex->Heigth()
			, bf);
	}

	CUI::Render(dc);
	CUI::RenderChild(dc);
}


void CSliderBar::MouseOn()
{

}

void CSliderBar::MouseLbtnDown()
{
	mbDrag = true;
	mvDragStartPos = MOUSE_POS;
}

void CSliderBar::MouseLbtnUp()
{
	mbDrag = false;
}