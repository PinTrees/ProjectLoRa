#pragma once
#include "CUI.h"


class CTexture;
class CSliderBar;


class CSlider :
	public CUI
{
private:
	CTexture* mpRoadTex;
	CSliderBar* mpSliderBar;

	int mMaxValue;
	int mLowValue;
	int mCurValue;


public:
	void SetMaxValue(int val) { mMaxValue = val; }
	void SetLowValue(int val) { mLowValue = val; }


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;
	CLONE(CSlider);


public:
	CSlider();
	virtual ~CSlider();
};

