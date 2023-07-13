#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

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


<<<<<<< Updated upstream
void CTexture::CREATE(UINT width, UINT heigth, COLORREF color)
=======
void CTexture::Create(UINT width, UINT heigth, COLORREF color)
>>>>>>> Stashed changes
{
	HDC mainDc = CCore::GetI()->GetMainDC();

	mhBit = CreateCompatibleBitmap(mainDc, width, heigth);
	mDC = CreateCompatibleDC(mainDc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, mhBit);
	DeleteObject(hOldBit);

	// Bitmap Info Data Setting
	GetObject(mhBit, sizeof(BITMAP), &mBitInfo);
}
