#pragma once
#include "CUI.h"



class CWrap :
	public CUI
{
private:
	float	mSpacingWidth;
	float	mSpacingHeight;


public:
	void SetSpacingWidth(float val) { mSpacingWidth = val; };
	void SetSpacingHeight(float val) { mSpacingHeight = val; };


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};


	CLONE(CWrap);


public:
	CWrap();
	~CWrap();
};
