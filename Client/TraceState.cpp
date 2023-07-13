#include "pch.h"
#include "TraceState.h"

// System Manager Header
#include "CTimeMgr.h"

// Manager Header
#include "PlayerMgr.h"

// GameObject Header
#include "Player.h"
#include "Monster.h"

// Components Header
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
	GetOwner()->GetAnimator()->Play(L"RUN", true);
}


void TraceState::Update()
{
	Monster* monster = (Monster*)GetOwner();

	if (monster->GetInfo().curHp <= 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		return;
	}

	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	Vect2 vMonsterPos = GetOwner()->GetLocalPos();
	Vect2 vMonsterDir = (vPlayerPos - vMonsterPos).Normalize();

	Vect2 vPos = vMonsterDir * monster->GetInfo().speed * DT;
	GetOwner()->SetPos(vPos + GetOwner()->GetPos());

	// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < monster->GetInfo().atkRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
	}
}


void TraceState::Exit()
{
}