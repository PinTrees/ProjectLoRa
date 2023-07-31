#pragma once


class SettingUI;
class CImageUI;
class TextUI;


class GUIMgr
{
	SINGLE(GUIMgr);

private:
	CImageUI*	mpBackground;
	SettingUI*	mpSettinUI;

	TextUI*		mFrameText;


public:
	void Init();

	void ShowSettingUI();
	void CloseSettingUI();

	void SetFrameText(UINT frame);
};

