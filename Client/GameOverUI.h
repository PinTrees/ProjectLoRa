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


public:
	void Close();
	void Show();
	void Build();


public:
	GameOverUI();
	~GameOverUI();
};

