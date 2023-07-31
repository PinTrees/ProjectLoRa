#include "pch.h"
#include "CombatText.h"

#include "CTimeMgr.h"




CombatText::CombatText()
	: mDeleteDelay(1.f)
	, mCurDelay(0.f)
{
	SetFontSize(28.f);
	SetColor(RGB(255, 0, 0));
	SetOutlineColor(RGB(0, 0, 0));
	SetOutlineWidth(2);

	SetCameraAffected(true);
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
	vPos += Vect2::up * 50.f * DT;

	SetPos(vPos);
}
