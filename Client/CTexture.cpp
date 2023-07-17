#include "pch.h"
#include "CTexture.h"

#include "CCore.h"
#include "SelectGDI.h"

CTexture::CTexture()
	:mhBit(0)
	, mDC(0)
	, mBitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(mDC);
	DeleteObject(mhBit);
}


void CTexture::Load(const wstring& strFilePath)
{
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	mhBit = (HBITMAP)LoadImage(nullptr, strFilePath.c_str(), IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(mhBit);

	// 비트맵과 연결할 DC
	mDC = CreateCompatibleDC(CCore::GetI()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(mDC, mhBit);
	DeleteObject(hPrevBit);

	// Bitmap Info Data Setting
	GetObject(mhBit, sizeof(BITMAP), &mBitInfo);
}


void CTexture::Create(UINT width, UINT height, COLORREF color)
{
	HDC mainDc = CCore::GetI()->GetMainDC();

	mhBit = CreateCompatibleBitmap(mainDc, width, height);
	mDC = CreateCompatibleDC(mainDc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, mhBit);
	DeleteObject(hOldBit);

	// 비트맵을 주어진 색상으로 채움
	HBRUSH hBrush = CreateSolidBrush(color);
	RECT rect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	FillRect(mDC, &rect, hBrush);
	DeleteObject(hBrush);

	// 비트맵 정보 설정
	GetObject(mhBit, sizeof(BITMAP), &mBitInfo);
}
