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
	, mpTexture(nullptr)
	, mType(IMAGE_TYPE::DEFAULT)
	// mType: Filled 
	, mFilledAxis(IAMGE_FILLED_AXIS::HORIZONTAL)
	, mFilledDirection(RECT_DIRECTION::LEFT)
	, mFilledAmount(1.f)
{
	// 모든 이미지는 단색 텍스쳐를 보유, 텍트쳐가 없을 경우 해당 텍스쳐를 출력합니다.
	// 이미지의 RGB 값을 바탕으로한 단색 텍스쳐를 생성
	mDefaultTex = CResMgr::GetI()->CreateTexture(L"SolidTex_"
		+ std::to_wstring(GetRValue(mColor)) + L","
		+ std::to_wstring(GetGValue(mColor)) + L","
		+ std::to_wstring(GetBValue(mColor)), 128, 128, mColor);
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
		+ std::to_wstring(GetGValue(mColor)) + L","
		+ std::to_wstring(GetBValue(mColor)), 128, 128, mColor);
}

void CImageUI::Render(HDC dc)
{
	if (GetAnimator())
	{
		GetAnimator()->GetCurAnimation()->RenderUI(this, dc);
		return;
	}

	// Set Render Pos and Scale
	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vSize = GetScale();

	// Set Render Texture
	CTexture* pRenderTex = (!mpTexture) ? mDefaultTex : mpTexture;

	// AlpaBlend Option Setting
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = (!mpTexture) ? 0 : AC_SRC_ALPHA;
	bf.SourceConstantAlpha = GetAlpha();

	// Default Image Render Mode 
	if (mType == IMAGE_TYPE::DEFAULT)
	{
		AlphaBlend(dc
			, (int)(vPos.x - vSize.x * 0.5f)
			, (int)(vPos.y - vSize.y * 0.5f)
			, (int)vSize.x
			, (int)vSize.y
			, pRenderTex->GetDC()
			, 0, 0
			, (int)pRenderTex->Width()
			, (int)pRenderTex->Heigth(), bf);
	}
	// Filled Image Render Mode
	else if (mType == IMAGE_TYPE::FILLED)
	{
		// Filled Scale x Calcurate
		float adjustedWidth = vSize.x * mFilledAmount;

		AlphaBlend(dc
			, (int)(vPos.x - vSize.x * 0.5f)
			, (int)(vPos.y - vSize.y * 0.5f)
			, (int)adjustedWidth
			, (int)vSize.y
			, pRenderTex->GetDC()
			, 0, 0
			, (int)pRenderTex->Width()
			, (int)pRenderTex->Heigth(), bf);
	}

	CUI::RenderChild(dc);
}

