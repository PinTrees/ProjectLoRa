#include "pch.h"
#include "BTraceState.h"
#include "PlayerMgr.h"
#include "Player.h"

#include "Boss.h"
#include "CTimeMgr.h"

#include "CAnimator.h"

BTraceState::BTraceState()
	: CState(MONSTER_STATE::TRACE)
	, mAvailable(true)
	, fCurSkillCool()
	, fSkillCool(4.f)

{
}

BTraceState::~BTraceState()
{
	
}


void BTraceState::Enter()
{
}

void BTraceState::Update()
{
	fCurSkillCool += DT;

	Vect2 vMonsterPos = GetOwner()->GetLocalPos();
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	GetOwner()->GetAnimator()->Play(vMonsterPos.x > vPlayerPos.x ? L"RUN_L" : L"RUN_R", true);

	Vect2 dir = (vPlayerPos - vMonsterPos).Normalize();
	GetOwner()->SetPos(GetOwner()->GetPos() + dir * 80.f * DT);

	if (Vect2::Distance(vPlayerPos, vMonsterPos) < 500.f 
		&& fCurSkillCool > fSkillCool)
	{
		fCurSkillCool = 0.f;
		ChangeAIState(GetAI(), MONSTER_STATE::SKILLATK);
	}
}

void BTraceState::Exit()
{
}
