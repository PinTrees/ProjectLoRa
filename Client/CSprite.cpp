#include "pch.h"
#include "CSprite.h"

#include "CCore.h"
#include "CPathMgr.h"


CSprite::CSprite()
	: mDC(0)
	, mImage(nullptr)
	, mRenderType(SPRITE_RENDER_TYPE::NORMAL)
	, mWidth(0)
	, mHeight(0)
{
}

CSprite::~CSprite()
{
	DeleteDC(mDC);

	if(nullptr != mImage)
		delete mImage;
}


void CSprite::Load(const wstring& strFilePath)
{
	mImage = Image::FromFile((WCHAR*)strFilePath.c_str());
	assert(mImage);

	mWidth = mImage->GetWidth();
	mHeight = mImage->GetHeight();

	// HDC »ý¼º
	mDC = CreateCompatibleDC(CCore::GetI()->GetMainDC());
}


void CSprite::Render(HDC dc, Vect2 vPos, Vect2 vSize)
{
	if (nullptr == mImage)
		return;

	if (SPRITE_RENDER_TYPE::NORMAL == mRenderType)
	{
		Gdiplus::Graphics g(dc);
		g.DrawImage(mImage
			, (INT)(vPos.x - vSize.x * 0.5f)
			, (INT)(vPos.y - vSize.y * 0.5f)
			, (INT)vSize.x
			, (INT)vSize.y);
	}
	else if (SPRITE_RENDER_TYPE::POINT == mRenderType)
	{
		RectF destRect(vPos.x - vSize.x * 0.5f, vPos.y - vSize.y * 0.5f, vSize.x, vSize.y);

		Gdiplus::Graphics g(dc);
		g.DrawImage(mImage
			, destRect
			, (INT)0
			, (INT)0
			, (INT)mWidth
			, (INT)mHeight
			, Unit::UnitPixel
			, NULL
			, NULL
			, NULL);
	}
}

