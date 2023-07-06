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

	// ������ �ʿ��� �ڵ��Դϴ�.
	// Ÿ���� ������� ��Ʈ���� ����� �ٸ��Ƿ� �ؽ����� ũ�� ���� �������ڰ� �߰��� �ʿ��մϴ�.
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

