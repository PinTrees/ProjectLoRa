#include "pch.h"
#include "TextUI.h"

#include "CFont.h"
#include "CResMgr.h"

TextUI::TextUI()
	: CUI(true)
	, mFont(nullptr)
	, mText(L"")
{
	// Base Font Setting
	mFont = CResMgr::GetI()->LoadFont(L"DungGeunMo", L"font\\DungGeunMo.ttf", 28, false);
}

TextUI::~TextUI()
{
}


void TextUI::SetText(const wstring& text)
{
	mText = text;
}


void TextUI::Render(HDC dc)
{
	if (nullptr == mFont || mText == L"")
		return;

	Vect2 vRenderPos = GetFinalPos();

	if (!IsCameraAffected())
	{
		vRenderPos = CCamera::GetI()->GetRenderPos(vRenderPos);
	}

	mFont->PrintWord(dc, vRenderPos, mText);
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


