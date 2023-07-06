#include "pch.h"
#include "IdleState.h"

IdleState::IdleState()
	: CState(MONSTER_STATE::IDLE)
{
}


IdleState::~IdleState()
{
}


void IdleState::Update()
{
	// 플레이어와의 거리 확인
	// 추적 범위내 진입시 추적
}

void IdleState::Enter()
{
}

void IdleState::Exit()
{
}

