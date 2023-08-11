#include "pch.h"
#include "CSlider.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CImageUI.h"

#include "CSliderBar.h"


CSlider::CSlider()
	: CUI(false)
{
	mpRoad = new CImageUI;
	mpRoad->SetName(L"SliderRoad");
	mpRoad->SetScale(Vect2(4.f, 10.f));
	mpRoad->SetColor(RGB(137, 90, 69));
	AddChild(mpRoad);

	mpSliderBar = new CSliderBar;
	AddChild(mpSliderBar);
}

CSlider::~CSlider()
{
}


void CSlider::Update()
{
	CUI::Update();

	mpRoad->SetScale(Vect2(4.f, GetScale().y));
}


void CSlider::Render(HDC dc)
{
}

