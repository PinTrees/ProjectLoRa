#include "pch.h"
#include "CFont.h"

#include "CUI.h"

CFont::CFont(HDC _dc)
	: mDC(_dc)
	, mDefaultFont(0)
	, mInnerColor(0)
	, mOuterColor(0)
	, mBorder(false)
{
}

CFont::~CFont()
{
	RemoveFontResource(GetRelativePath().c_str());
}


void CFont::Load(const wstring& filePath, const wstring& name, int size, bool _border)
{
	AddFontResource(filePath.c_str());

	// ��Ʈ�� ũ�Ⱚ�� ���ҽ� Ű�� �� ��Ʈ �̸��� �߰�
	// ���� ��Ʈ�� �ٸ� ũ��� ��µ� �� ����
	// name.c_str() �� ������ �� ����. �ܺο��� ���ҽ� Key ���� �߰�
	mBorder = _border;
	mDefaultFont = CreateFont(size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, name.c_str());
}


void CFont::Render(HDC dc, const wstring& str, Vect2 pos, Vect2 scale)
{
	HFONT hOldFont = (HFONT)SelectObject(dc, mDefaultFont);
	SetBkMode(dc, TRANSPARENT);


	SIZE textSize;
	GetTextExtentPoint32(dc, str.c_str(), (int)(str.size()), &textSize);

	int textX = (int)(pos.x - textSize.cx * 0.5f);
	int textY = (int)(pos.y - textSize.cy * 0.5f);

	if (mBorder)
	{
		SetTextColor(dc, mOuterColor);
		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j)
				TextOut(dc, textX + i, textY + j, str.c_str(), (int)str.size());
	}

	SetTextColor(dc, mInnerColor);
	TextOut(dc, textX, textY, str.c_str(), (int)(str.size()));

	SelectObject(dc, hOldFont);
}
