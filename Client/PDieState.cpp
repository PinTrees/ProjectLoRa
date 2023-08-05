#include "pch.h"
#include "PDieState.h"

#include "PlayerMgr.h"

#include "Player.h"
#include "CAnimator.h"
#include "CAnimation.h"

PDieState::PDieState()
	: CState(PLAYER_STATE::Die)
{
}

PDieState::~PDieState()
{
}

void PDieState::Update()
{
	Player* pPlayer = (Player*)GetOwner();
	if (pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void PDieState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();

	pPlayer->GetAnimator()->Play(L"DIE", false);
}

void PDieState::Exit()
{
}
