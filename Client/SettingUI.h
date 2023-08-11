#pragma once
#include "CPanelUI.h"


class CBtnUI;
class CImageUI;

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

public:
	void Close();
	void Show();
	void Build();


public:
	void SetFindPath(DWORD_PTR param);
	void SetDebugMode();
	void SetDamageText();


public:
	SettingUI();
	virtual ~SettingUI() override;
	SettingUI(SettingUI&) = delete;
};

