#pragma once
#include "CUI.h"

typedef void(CObject::* SLIDER_OBJ) (DWORD_PTR);

class CImageUI;
class CSliderBar;
class CObject;


class CSlider :
	public CUI
{
private:
	CImageUI*	mpRoad;
	CSliderBar* mpSliderBar;

	CObject*	mFuncOwner;
	SLIDER_OBJ	mSliderFunc;

	float mRatio;

	int mMaxValue;
	int mLowValue;
	int mCurValue;


public:
	void SetMaxValue(int val) { mMaxValue = val; }
	void SetLowValue(int val) { mLowValue = val; }
	void SetValue(int val);

	void SetHorSliderValue();

	void SetSliderFunc(CObject* obj, SLIDER_OBJ func) { mFuncOwner = obj; mSliderFunc = func; }


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;
	CLONE(CSlider);


public:
	CSlider();
	virtual ~CSlider();
};

