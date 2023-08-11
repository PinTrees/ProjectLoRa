#include "pch.h"
#include "BTraceState.h"
#include "PlayerMgr.h"
#include "Player.h"

#include "Boss.h"
#include "CTimeMgr.h"


BTraceState::BTraceState()
	: CState(MONSTER_STATE::TRACE)
	, mAvailable(true)
	,fCurSkillCool()
	,fSkillCool(4.f)

{
}

BTraceState::~BTraceState()
{
}

void BTraceState::Update()
{

	Vect2 vMonsterPos = GetOwner()->GetPos();
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();


	Vect2 dir = vPlayerPos - vMonsterPos;
	dir.Normalize();
	GetOwner()->SetPos(vMonsterPos + dir * 100.f * DT);
	fCurSkillCool += DT;
	Vect2 r=  vPlayerPos - vMonsterPos;
	if (r.Length() < 700.f && fCurSkillCool > fSkillCool)
	{
		fCurSkillCool = 0;
		ChangeAIState(GetAI(), MONSTER_STATE::SKILLATK);
	}
}

void BTraceState::Enter()
{
}

void BTraceState::Exit()
{
}

