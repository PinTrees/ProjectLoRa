#include "pch.h"
#include "CImageUI.h"

#include "SelectGDI.h"
#include "CTexture.h"

#include "CAnimator.h"
#include "CAnimation.h"

CImageUI::CImageUI()
	: CUI(false)
{
}

CImageUI::~CImageUI()
{
}



void CImageUI::Render(HDC dc)
{
	if (GetAnimator())
	{
		GetAnimator()->GetCurAnimation()->RenderUI(this, dc);
		return;
	}

	Vect2 vPos = GetFinalPos();
	Vect2 vScale = GetScale();

	if (IsCameraAffected())
	{
		vPos = CCamera::GetI()->GetRenderPos(vPos);
	}

	if(mpTexture)
	{
		float fWidth = (float)mpTexture->Width();
		float fHeight = (float)mpTexture->Heigth();

		TransparentBlt(dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)vScale.x
			, (int)vScale.y
			, mpTexture->GetDC()
			, 0, 0
			, (int)fWidth, (int)fHeight
			, RGB(255, 0, 255));
	}

	CUI::RenderChild(dc);
}

