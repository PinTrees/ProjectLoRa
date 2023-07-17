#pragma once
#include "CUI.h"



class CColumn :
	public CUI
{
private:
	ALIGNMENT		mAlignment;
	float			mSpacing;

public:
	void SetAlignment(ALIGNMENT alignment) { mAlignment = alignment; }
	void SetSpacing(float spacing) { mSpacing = spacing; }


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CColumn);


public:
	CColumn();
	virtual ~CColumn() override;
};
