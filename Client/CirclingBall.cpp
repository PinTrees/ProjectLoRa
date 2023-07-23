#include "pch.h"
#include "CirclingBall.h"

#include "PlayerMgr.h"

#include "Player.h"
#include "CirclingBall_Obj.h"

CirclingBall::CirclingBall()
	: Skill(SKILL_TYPE::CIRCLING_BALL, 5)
	, mPrevLv(1)
{
	SetCoolDown(0.f);		// 쿨타임 세팅
}

CirclingBall::~CirclingBall()
{
}


void CirclingBall::UseSkill()
{
	float Theta;
	Theta = 2 * PI / GetSkillLevel();			// 레벨에 따라 공의 개수가 증가하는데 공의 위치를 일정하게 잡기 위한 값

	for (int i = 0; i < GetSkillLevel(); ++i)
	{
		CirclingBall_Obj* pBall = new CirclingBall_Obj;		// 레벨 수 만큼 공을 생성
		pBall->SetOwner(this);
		pBall->SetTheta(Theta * i);
		pBall->SetPrevLv(GetSkillLevel());

		CreateObject(pBall, GROUP_TYPE::PROJ_PLAYER);
	}
}

void CirclingBall::CheckAvailable()
{
	if (mPrevLv < GetSkillLevel())		// 레벨업을 하면 바로 공이 새로 생성되도록 하기위해 사용가능상태로 세팅
	{
		SetAvailable(true);
		mPrevLv = GetSkillLevel();
	}
}