#pragma once
#include "CUI.h"



class CWrap :
	public CUI
{
private:


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override { CUI::MouseOn(); };
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CWrap);


public:
	CWrap();
	~CWrap();
};
