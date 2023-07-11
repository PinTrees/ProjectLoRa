#include "pch.h"
#include "AtkState.h"

// Components Header
#include "CAnimator.h"
#include "CAnimation.h"

#include "Monster.h"




AtkState::AtkState()
	: CState(MONSTER_STATE::ATTACK)
{
}


AtkState::~AtkState()
{
}


void AtkState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"ATK", false);
}


void AtkState::Update()
{
	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
}


void AtkState::Exit()
{
}