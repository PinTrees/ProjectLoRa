#include "pch.h"
#include "TextUI.h"

#include "CFont.h"
#include "CResMgr.h"




TextUI::TextUI()
	: CUI(true)
	, mFont(nullptr)
	, mText(L"")
	, mStyle({})
{
	// Base Font Setting
	mStyle.fontSize = 32;
	mFont = CResMgr::GetI()->LoadFont(L"DungGeunMo", L"font\\DungGeunMo.ttf", mStyle.fontSize, false);
}

TextUI::~TextUI()
{
}


void TextUI::SetText(const wstring& text)
{
	mText = text;
}

void TextUI::SetFontSize(float size)
{
	if (mStyle.fontSize == size)
		return;

	mStyle.fontSize = size;
	
	// ReLoad Font
	mFont = CResMgr::GetI()->LoadFont(L"DungGeunMo", L"font\\DungGeunMo.ttf", mStyle.fontSize, false);
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

	mFont->Render(dc, mText, vRenderPos, GetScale());
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


