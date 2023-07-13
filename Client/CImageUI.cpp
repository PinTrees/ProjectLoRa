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
}

