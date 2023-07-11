#include "pch.h"
#include "CFont.h"



CFont::CFont(HDC _dc)
	: mDC(_dc)
	, mDefaultFont(0)
	, mStr{}
	, mInnerColor(0)
	, mOuterColor(0)
	, mBorder(false)
{
}

CFont::~CFont()
{
	SelectObject(mDC, mDefaultFont);
}


void CFont::Create(const wstring& _filePath)
{
	AddFontResource(_filePath.c_str());
}

void CFont::SelectFont(int _size, const wstring& _name, bool _border)
{
	mBorder = _border;
	HFONT hFont = CreateFont(
		/* 폰트의 크기와 스타일을 지정합니다. */
		_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		/* 폰트 이름을 지정합니다. */
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _name.c_str()
	);
	mDefaultFont = (HFONT)SelectObject(mDC, hFont);
	DeleteObject(hFont);
}

void CFont::DeleteFont(const wstring& _filePath)
{
	RemoveFontResource(_filePath.c_str());
}

void CFont::PrintWord(HDC dc, Vect2 _vPos)
{
	if (mBorder)
	{
		SetTextColor(dc, mOuterColor);
		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j)
				TextOut(dc, (int)_vPos.x + i, (int)_vPos.y + j, mStr.c_str(), (int)mStr.size());
	}

	SetTextColor(dc, mInnerColor);
	TextOut(dc, (int)_vPos.x, (int)_vPos.y, mStr.c_str(), (int)mStr.size());
}
