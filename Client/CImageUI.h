#pragma once
#include "CUI.h"



class CTexture;


class CImageUI :
	public CUI
{
private:
	CTexture* mDefaultTex;
	COLORREF  mColor;


public:
	void SetColor(COLORREF color);


public:
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CImageUI);


public:
	CImageUI();
	~CImageUI() override;
};

