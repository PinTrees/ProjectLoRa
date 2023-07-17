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
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	mhBit = (HBITMAP)LoadImage(nullptr, strFilePath.c_str(), IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(mhBit);

	// ��Ʈ�ʰ� ������ DC
	mDC = CreateCompatibleDC(CCore::GetI()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
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

	// ��Ʈ���� �־��� �������� ä��
	HBRUSH hBrush = CreateSolidBrush(color);
	RECT rect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	FillRect(mDC, &rect, hBrush);
	DeleteObject(hBrush);

	// ��Ʈ�� ���� ����
	GetObject(mhBit, sizeof(BITMAP), &mBitInfo);
}
