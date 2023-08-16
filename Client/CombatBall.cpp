#include "pch.h"
#include "CombatBall.h"
#include "CombatBall_Obj.h"

#include "PlayerMgr.h"

#include "Player.h"




CombatBall::CombatBall()
	: Skill(SKILL_TYPE::COMBAT_BALL, 8)
	, mPrevLv(1)
{
	SetIconStr(L"9.bmp");
	SetCoolDown(1.f);
}

CombatBall::~CombatBall()
{
}


void CombatBall::UseSkill()
{
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	CombatBall_Obj* ball = new CombatBall_Obj;

	ball->SetOwner(this);
	ball->SetPos(vPlayerPos);

	CreateObject(ball, GROUP_TYPE::PROJ_PLAYER);
}

void CombatBall::CheckAvailable()
{
	if (mPrevLv > GetSkillLevel())
	{
		SetAvailable(true);
		mPrevLv = GetSkillLevel();
	}
}

void CombatBall::AddSkillLevel()
{
	Skill::AddSkillLevel();

	float newCoolDown = GetCoolDown() - 0.1f * GetSkillLevel();
	SetCoolDown(newCoolDown);
}
