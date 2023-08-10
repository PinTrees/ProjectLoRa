#pragma once
#include "CImageUI.h"


class TextUI;
class CImageUI;
class CBtnUI;


class GameOverUI :
	public CImageUI
{
private:
	TextUI*		mpTitle;
	CBtnUI*		mpMainSceneBtn;

	float	mFadeDelay;
	float	mCurDelay;
	bool	mbFade;


public:
	void Close();
	void Show();
	void Build();


public:
	virtual void Update() override;


public:
	GameOverUI();
	virtual ~GameOverUI() override;
};

