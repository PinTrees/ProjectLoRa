#pragma once


class SettingUI;
class CImageUI;
class TextUI;
class CBtnUI;
class GameOverUI;


class GUIMgr
{
	SINGLE(GUIMgr);

private:
	CImageUI*	mpBackground;
	SettingUI*	mpSettinUI;

	TextUI*		mFrameText;
	CBtnUI*		mpSettingBtn;
	GameOverUI* mpGameOverUI;

	TextUI*		mTimerText;


public:
	void Init();

	void ShowSettingUI();
	void CloseSettingUI();

	void ShowGameOverUI();
	void CloseGameOverUI();

	void SetFrameText(UINT frame);
	void SetTimerText(UINT timer);
};

