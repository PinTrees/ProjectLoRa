#pragma once

#include "TextUI.h"

class CombatText
	: public TextUI
{
private:
	float	mDeleteDelay;
	float	mCurDelay;


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;


public:
	CombatText();
	virtual ~CombatText() override;
};

