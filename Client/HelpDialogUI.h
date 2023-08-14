#pragma once
#include "CImageUI.h"


class TextUI;
class CImageUI;
class CBtnUI;


class HelpDialogUI :
	public CImageUI
{
private:
	TextUI* mpTitle;
	CBtnUI* mpMainSceneBtn;

	float	mFadeDelay;
	float	mCurDelay;
	bool	mbFade;


public:
	void Close();
	void Build();


public:
	virtual void Update() override;


public:
	HelpDialogUI();
	virtual ~HelpDialogUI() override;
};

