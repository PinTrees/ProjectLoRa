#include "pch.h"
#include "HolyArea.h"
#include "HolyArea_Obj.h"
#include "CCollider.h"

HolyArea::HolyArea()
	: Skill(SKILL_TYPE::HOLYAREA, /*6*/1)
	, mPrevLv(1)
{
	SetIconStr(L"5.bmp");
	SetCoolDown(0.f);
}

HolyArea::~HolyArea()
{
}


void HolyArea::UseSkill()
{
	HolyArea_Obj* area = new HolyArea_Obj;
	area->SetOwner(this);
	area->SetPrevLv(GetSkillLevel());
	area->GetCollider()->SetScale(Vect2(65.f, 65.f) + Vect2(50.f, 50.f) * GetSkillLevel());
	area->SetScale(Vect2(80.f, 80.f) + Vect2(50.f, 50.f) * GetSkillLevel());

	CreateObject(area, GROUP_TYPE::GROUND_PLAYER);
}

void HolyArea::CheckAvailable()
{
	if (mPrevLv < GetSkillLevel())
	{
		SetAvailable(true);
		mPrevLv = GetSkillLevel();
	}
}