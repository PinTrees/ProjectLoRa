#include "pch.h"
#include "TraceState.h"

<<<<<<< Updated upstream
#include "CTimeMgr.h"

#include "PlayerMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CAnimator.h"


=======
// System Manager Header
#include "CTimeMgr.h"

// Manager Header
#include "PlayerMgr.h"

// GameObject Header
#include "Player.h"
#include "Monster.h"

// Components Header
#include "CAnimator.h"




>>>>>>> Stashed changes
TraceState::TraceState()
	: CState(MONSTER_STATE::TRACE)
{
}


TraceState::~TraceState()
{
}


void TraceState::Enter()
{
<<<<<<< Updated upstream
	GetMonster()->GetAnimator()->Play(L"RUN", true);
=======
	GetOwner()->GetAnimator()->Play(L"RUN", true);
>>>>>>> Stashed changes
}


void TraceState::Update()
{
<<<<<<< Updated upstream
	if (GetMonster()->GetInfo().curHp <= 0)
=======
	Monster* monster = (Monster*)GetOwner();

	if (monster->GetInfo().curHp <= 0)
>>>>>>> Stashed changes
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		return;
	}

<<<<<<< Updated upstream
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetLocalPos();

	Vec2 vMonsterPos = GetMonster()->GetLocalPos();
	Vec2 vMonsterDir = (vPlayerPos - vMonsterPos).Normalize();

	Vec2 vPos = vMonsterDir * GetMonster()->GetInfo().speed * DT;
	GetMonster()->SetPos(vPos + GetMonster()->GetPos());

	// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vec2::Distance(vPlayerPos, vMonsterPos) < GetMonster()->GetInfo().atkRange)
=======
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	Vect2 vMonsterPos = GetOwner()->GetLocalPos();
	Vect2 vMonsterDir = (vPlayerPos - vMonsterPos).Normalize();

	Vect2 vPos = vMonsterDir * monster->GetInfo().speed * DT;
	GetOwner()->SetPos(vPos + GetOwner()->GetPos());

	// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < monster->GetInfo().atkRange)
>>>>>>> Stashed changes
	{
		ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
	}
}


void TraceState::Exit()
{
}