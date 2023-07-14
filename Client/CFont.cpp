#include "pch.h"
#include "CFont.h"



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
}


void CFont::Create(const wstring& _filePath)
{
	AddFontResource(_filePath.c_str()); 
}

void CFont::SelectFont(int _size, const wstring& _name, bool _border)
{ 
	mBorder = _border;
	mDefaultFont = CreateFont(_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _name.c_str());
}

void CFont::DeleteFont(const wstring& _filePath)
{
	RemoveFontResource(_filePath.c_str());
}

void CFont::PrintWord(HDC dc, Vect2 _vPos, const wstring& str)
{
	HFONT hOldFont = (HFONT)SelectObject(dc, mDefaultFont);
	SetBkMode(dc, TRANSPARENT);

	SIZE textSize;
	GetTextExtentPoint32(dc, str.c_str(), (int)(str.size()), &textSize);

	int textX = (int)(_vPos.x - textSize.cx * 0.5f);
	int textY = (int)(_vPos.y - textSize.cy * 0.5f);

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
