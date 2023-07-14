#pragma once

#include "CUI.h"


struct tTextStyle
{
	float		fontSize;
	COLORREF	color;
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

