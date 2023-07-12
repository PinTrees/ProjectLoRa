#include "pch.h"
#include "CombatText.h"

#include "CTimeMgr.h"




CombatText::CombatText()
	: mDeleteDelay(1.f)
	, mCurDelay(0.f)
{
}

CombatText::~CombatText()
{
}


void CombatText::Render(HDC dc)
{
	TextUI::Render(dc);
}


void CombatText::Update()
{
	mCurDelay += DT;
	if (mCurDelay > mDeleteDelay)
	{
		DeleteObject(this);
	}

	Vect2 vPos = GetPos();
	vPos += Vect2::up * 100.f * DT;

	SetPos(vPos);
}
