#include "pch.h"
#include "CImageUI.h"

#include "SelectGDI.h"
#include "CTexture.h"


CImageUI::CImageUI()
	: CUI(false)
{
}

CImageUI::~CImageUI()
{
}



void CImageUI::Render(HDC dc)
{
	CUI::Render(dc);

	Vect2 vPos = GetFinalPos();
	Vect2 vScale = GetScale();

	if (IsCameraAffected())
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
	}

	if (IsLbtnDown())
	{
		SelectGDI p(dc, PEN_TYPE::GREEN);
	}

	if (nullptr == mpTexture)
		return;

	TransparentBlt(dc
		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)vScale.x
		, (int)vScale.y
		, mpTexture->GetDC()
		, 0, 0
		, (int)mpTexture->Width()
		, (int)mpTexture->Heigth()
		, RGB(255, 0, 255));
}

