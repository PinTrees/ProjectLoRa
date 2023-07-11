#include "pch.h"
#include "TextUI.h"

#include "CFont.h"
#include "CResMgr.h"

TextUI::TextUI()
	: CUI(false)
	, mFont(nullptr)
	, mText(L"")
{
	// Base Font Setting
	mFont = CResMgr::GetI()->LoadFont(L"DungGeunMo", L"font\\DungGeunMo.ttf", 24, 0);
}

TextUI::~TextUI()
{
}


void TextUI::SetText(const wstring& text)
{
	mText = text;
	mFont->SetWord(mText);
}


void TextUI::Render(HDC dc)
{
	if (nullptr != mFont && mText != L"")
	{
		mFont->PrintWord(dc, GetFinalPos());
	}
}

void TextUI::MouseOn()
{
}

void TextUI::MouseLbtnDown()
{
}

void TextUI::MouseLbtnUp()
{
}

void TextUI::MouseLbtnClick()
{
}


