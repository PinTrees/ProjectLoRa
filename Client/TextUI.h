#pragma once

#include "CUI.h"

class CFont;

class TextUI :
	public CUI
{
private:
	CFont*		 mFont;
	wstring		 mText;
	

public:
	void SetText(const wstring& text);


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
	~TextUI();
};

