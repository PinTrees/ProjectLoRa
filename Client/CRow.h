#pragma once
#include "CUI.h"



class CRow :
	public CUI
{
private:
	ALIGNMENT		mAlignment;


public:
	void SetAlignment(ALIGNMENT alignment) { mAlignment = alignment; }
	ALIGNMENT GetAlignment() { return mAlignment; }


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CRow);


public:
	CRow();
	~CRow();
};
