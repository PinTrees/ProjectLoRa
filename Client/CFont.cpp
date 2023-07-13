#include "pch.h"
#include "CFont.h"

<<<<<<< Updated upstream
=======


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


>>>>>>> Stashed changes
void CFont::Create(const wstring& _filePath)
{
	AddFontResource(_filePath.c_str());
}

void CFont::SelectFont(int _size, const wstring& _name, bool _border)
{
	mBorder = _border;
<<<<<<< Updated upstream
	HFONT hFont = CreateFont(
		/* 폰트의 크기와 스타일을 지정합니다. */
		_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		/* 폰트 이름을 지정합니다. */
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _name.c_str()
	);
	mDefaultFont = (HFONT)SelectObject(mDC, hFont);
	DeleteObject(hFont);
=======
	mDefaultFont = CreateFont(_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
>>>>>>> Stashed changes
}

void CFont::DeleteFont(const wstring& _filePath)
{
<<<<<<< Updated upstream
	RemoveFontResource(_filePath.c_str());
}

void CFont::PrintWord(Vec2 _vPos)
{
	if (mBorder)
	{
		SetTextColor(mDC, mOuterColor);
		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j)
				TextOut(mDC, (int)_vPos.x + i, (int)_vPos.y + j, mStr.c_str(), mStr.size());
	}

	SetTextColor(mDC, mInnerColor);
	TextOut(mDC, (int)_vPos.x, (int)_vPos.y, mStr.c_str(), mStr.size());
}

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
=======
	//RemoveFontResource(_filePath.c_str());
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
>>>>>>> Stashed changes
}
