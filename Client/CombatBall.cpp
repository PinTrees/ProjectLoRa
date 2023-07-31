#include "pch.h"
#include "CombatBall.h"
#include "CombatBall_Obj.h"

#include "PlayerMgr.h"

#include "Player.h"




CombatBall::CombatBall()
	: Skill(SKILL_TYPE::COMBAT_BALL, 6)
	, mPrevLv(1)
{
	SetCoolDown(0.2f);
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