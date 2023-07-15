#pragma once

#include "CUI.h"


struct tTextStyle
{
	float		fontSize;

	bool		boder;

	COLORREF	color;
	COLORREF    outerColor;
};


class CFont;

class TextUI :
	public CUI
{
private:
	CFont*		 mFont;
	wstring		 mText;
	tTextStyle	 mStyle;


public:
	void SetText(const wstring& text);
	void SetOutlineColor(COLORREF color) { mStyle.outerColor = color; mStyle.boder = true; }
	void SetColor(COLORREF color) { mStyle.color = color; }
	void SetFontSize(float size);


public:
	virtual void Render(HDC dc);


public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClick() override;

	CLONE(TextUI);


public:
	TextUI();
	virtual ~TextUI();
};

