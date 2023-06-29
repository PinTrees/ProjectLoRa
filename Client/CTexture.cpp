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

	// ��Ʈ�� ����
	GetObject(mhBit, sizeof(BITMAP), &mBitInfo);
}
