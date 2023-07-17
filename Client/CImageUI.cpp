#include "pch.h"
#include "CImageUI.h"

#include "SelectGDI.h"
#include "CTexture.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"




CImageUI::CImageUI()
	: CUI(false)
	, mColor(RGB(255, 255, 255))
	, mDefaultTex(nullptr)
{
	// 모든 이미지는 단색 텍스쳐를 보유, 텍트쳐가 없을 경우 해당 텍스쳐를 출력합니다.
	// 이미지의 RGB 값을 바탕으로한 단색 텍스쳐를 생성
	mDefaultTex = CResMgr::GetI()->CreateTexture(L"SolidTex_"
		+ std::to_wstring(GetRValue(mColor)) + L","
		+ std::to_wstring(GetRValue(mColor)) + L","
		+ std::to_wstring(GetRValue(mColor)), 128, 128, mColor);
}

CImageUI::~CImageUI()
{
}



void CImageUI::SetColor(COLORREF color)
{
	// 이미지의 RGB 값을 바탕으로한 단색 텍스쳐를 생성
	mColor = color;
	mDefaultTex = CResMgr::GetI()->CreateTexture(L"SolidTex_"
		+ std::to_wstring(GetRValue(mColor)) + L","
		+ std::to_wstring(GetRValue(mColor)) + L","
		+ std::to_wstring(GetRValue(mColor)), 128, 128, mColor);
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

	// 보유한 텍스쳐가 있을 경우 해당 텍스쳐를 출력
	if (GetTexture())
	{
		Vect2 vSize = GetScale();
		Vect2 vPos = GetFinalPos();

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = GetAlpha();

		AlphaBlend(dc
			, (int)vPos.x - vSize.x * 0.5f
			, (int)vPos.y - vSize.y * 0.5f
			, (int)vSize.x
			, (int)vSize.y
			, GetTexture()->GetDC()
			, 0, 0
			, (int)GetTexture()->Width()
			, (int)GetTexture()->Heigth(), bf);
	}
	// 보유한 텍스쳐가 없을 경우 단색 텍스쳐를 출력
	else if(mDefaultTex)
	{
		Vect2 vSize = GetScale();
		Vect2 vPos = GetFinalPos();

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = GetAlpha();

		AlphaBlend(dc
			, (int)vPos.x - vSize.x * 0.5f
			, (int)vPos.y - vSize.y * 0.5f
			, (int)vSize.x
			, (int)vSize.y
			, mDefaultTex->GetDC()
			, 0, 0
			, (int)mDefaultTex->Width()
			, (int)mDefaultTex->Heigth(), bf);
	}

	CUI::RenderChild(dc);
}

