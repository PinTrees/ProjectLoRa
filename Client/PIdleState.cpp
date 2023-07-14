#include "pch.h"
#include "PIdleState.h"


#include "Player.h"
#include "CAnimator.h"


PIdleState::PIdleState()
	: CState(PLAYER_STATE::IDLE)
{
}

PIdleState::~PIdleState()
{
}


void PIdleState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();
	pPlayer->GetAnimator()->Play(L"IDLE", true);
}

void PIdleState::Update()
{
}

void PIdleState::Exit()
{
}


