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
	CImageUI*	mCurSelectIcon;

	CBtnUI*		mDebugBtn;
	CImageUI*	mDebugCheckIcon;


public:
	void Close();
	void Show();
	void Build();


public:
	void SetFindPath(DWORD_PTR param);
	void SetDebugMode();


public:
	SettingUI();
	~SettingUI();
	SettingUI(SettingUI&) = delete;
};

