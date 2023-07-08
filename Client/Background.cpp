#include "pch.h"
#include "Background.h"

#include "CTexture.h"
#include "CResMgr.h"

Background::Background()
	: mParallaxTex(nullptr)
{
}

Background::~Background()
{
}


HDC Background::GetParallaxDC()
{
	return mParallaxTex->GetDC();
}


void Background::Render(HDC dc, Vec2 ltPos, Vec2 size)
{
	if (nullptr == mParallaxTex)
		return;

	// 변경이 필요한 코드입니다.
	// 타일의 사이즈와 비트맵의 사이즈가 다르므로 텍스쳐의 크롭 영역 벡터인자가 추가로 필요합니다.
	StretchBlt(dc
		, 0, 0
		, size.x, size.y
		, mParallaxTex->GetDC()
		, ltPos.x, ltPos.y
		, size.x, size.y
		, SRCCOPY);
}


void Background::CreateParallaxTexture(int width, int height)
{
	mParallaxTex = CResMgr::GetI()->CreateTexture(L"ParallaxBit1", (UINT)width, (UINT)height);
}


void Background::Update()
{
}

void Background::Render(HDC _dc)
{
}

