#include "pch.h"
#include "CSliderBar.h"

#include "CTexture.h"
#include "CResMgr.h"



CSliderBar::CSliderBar()
	: CUI(false)
{
	mpTex = CResMgr::GetI()->LoadTexture(L"SliderBar", L"texture\\ui\\slider\\bar.bmp");
}

CSliderBar::~CSliderBar()
{
}


void CSliderBar::Update()
{
	CUI::Update();
}

void CSliderBar::Render(HDC dc)
{
	if (mpTex)
	{

	}
}
