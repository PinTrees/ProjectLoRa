#pragma once


class SettingUI;
class CImageUI;
class TextUI;
class CBtnUI;


class GUIMgr
{
	SINGLE(GUIMgr);

private:
	CImageUI*	mpBackground;
	SettingUI*	mpSettinUI;

	TextUI*		mFrameText;

	CBtnUI*		mpSettingBtn;


public:
	void Init();

	void ShowSettingUI();
	void CloseSettingUI();

	void SetFrameText(UINT frame);
};

