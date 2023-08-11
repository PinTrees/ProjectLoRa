#pragma once
#include "CPanelUI.h"


class CBtnUI;
class CImageUI;
class CSlider;
class TextUI;


class SettingUI :
	public CPanelUI
{
private:
	CBtnUI*		mAstarBtn;
	CBtnUI*		mJPSBtn;

	CBtnUI*		mDebugBtn;
	CImageUI*	mDebugCheckIcon;

	CBtnUI*		mDamageTextBtn;
	CImageUI*	mDamageTextCheckIcon;

	CSlider*	mSoundSlider;
	TextUI*		mVolumText;


public:
	void Close();
	void Show();
	void Build();


public:
	void SetFindPath(DWORD_PTR param);
	void SetDebugMode();
	void SetDamageText();
	
	void ChangeSoundSliderValue(int val);


public:
	SettingUI();
	virtual ~SettingUI();
};

