#include "pch.h"
#include "CrossDagger.h"
#include "CrossDagger_Obj.h"

#include "Player.h"
#include "PlayerMgr.h"

CrossDagger::CrossDagger()
	: Skill(SKILL_TYPE::CROSS_DAGGER, 5)
	, mCount(4)
{
	SetCoolDown(3.f);
}

CrossDagger::~CrossDagger()
{
}


void CrossDagger::UseSkill()
{
	float Theta;
	Theta = 2 * PI / mCount;

	for (int i = 0; i < mCount; ++i)		// 정해진 개수만큼 표창 생성
	{
		CrossDagger_Obj* pDagger = new CrossDagger_Obj;
		pDagger->SetOwner(this);
		pDagger->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
		pDagger->SetTheta(Theta * i);		// 표창의 간격이 일정하도록 계산

		CreateObject(pDagger, GROUP_TYPE::PROJ_PLAYER);
	}
	
	SetSkillTime(0.f);
}

void CrossDagger::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // 쿨타임이 끝나면 다시 사용가능 상태로 세팅
	{
		SetAvailable(true);
	}
}