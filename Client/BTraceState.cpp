#include "pch.h"
#include "BTraceState.h"
#include "PlayerMgr.h"
#include "Player.h"

#include "CTimeMgr.h"


BTraceState::BTraceState()
	: CState(MONSTER_STATE::TRACE)
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
}

void BTraceState::Enter()
{
}

void BTraceState::Exit()
{
}

