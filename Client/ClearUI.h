#pragma once
#include "CImageUI.h"


class TextUI;
class CBtnUI;
class CRow;
class CBtnUI;


class ClearUI :
	public CImageUI
{
private:
	TextUI* mpTitle;
	CBtnUI* mpMainSceneBtn;

	TextUI* mpSkillTitle;
	CRow*	mpSkillListUI;
	CBtnUI* mpExiteBtn;


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
	void changeMainScene();


public:
	ClearUI();
	~ClearUI();
};

