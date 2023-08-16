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

	CBtnUI*		mShowHpBarBtn;
	CImageUI*	mShowHpBarTextCheckIcon;

	CSlider*	mSoundSlider;
	TextUI*		mVolumText;

	CSlider*	mBgmSoundSlider;
	TextUI*		mBgmVolumText;

	CBtnUI*		mResBtn[3];
	CImageUI*	mResCheckIcon[3];

public:
	void Close();
	void Show();
	void Build();


public:
	void SetFindPath(DWORD_PTR param);
	void SetDebugMode();
	void SetDamageText();
	void SetShowMonsterHpBar();
	
	void SetResolution(int i);

	void ChangeSoundSliderValue(int val);
	void ChangeBGMSoundSliderValue(int val);


public:
	SettingUI();
	virtual ~SettingUI();
};

