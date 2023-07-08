#include "pch.h"
#include "TraceState.h"

#include "CTimeMgr.h"

#include "PlayerMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CAnimator.h"


TraceState::TraceState()
	: CState(MONSTER_STATE::TRACE)
{
}


TraceState::~TraceState()
{
}


void TraceState::Enter()
{
	GetMonster()->GetAnimator()->Play(L"RUN", true);
}


void TraceState::Update()
{
	if (GetMonster()->GetInfo().curHp <= 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		return;
	}

	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetLocalPos();

	Vec2 vMonsterPos = GetMonster()->GetLocalPos();
	Vec2 vMonsterDir = (vPlayerPos - vMonsterPos).Normalize();

	Vec2 vPos = vMonsterDir * GetMonster()->GetInfo().speed * DT;
	GetMonster()->SetPos(vPos + GetMonster()->GetPos());

	// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vec2::Distance(vPlayerPos, vMonsterPos) < GetMonster()->GetInfo().atkRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
	}
}


void TraceState::Exit()
{
}