#pragma once


class SettingUI;
class CImageUI;
class TextUI;
class CBtnUI;
class GameOverUI;
class ClearUI;
class CSound;


class GUIMgr
{
	SINGLE(GUIMgr);

private:
	CImageUI*	mpBackground;
	SettingUI*	mpSettinUI;

	TextUI*		mFrameText;
	CBtnUI*		mpSettingBtn;
	GameOverUI* mpGameOverUI;
	ClearUI*	mpGameClearUI;

	TextUI*		mTimerText;
	CSound*		mClearScound;


public:
	void Init();

	void ShowSettingUI();
	void CloseSettingUI();

	void ShowGameOverUI();
	void CloseGameOverUI();

	void ShowGameClearUI();
	void CloseGameClearUI();

	void SetFrameText(UINT frame);
	void SetTimerText(UINT timer);
};

