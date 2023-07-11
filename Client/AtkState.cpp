#include "pch.h"
#include "AtkState.h"

#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"




AtkState::AtkState()
	: CState(MONSTER_STATE::ATTACK)
{
}


AtkState::~AtkState()
{
}


void AtkState::Enter()
{
	GetMonster()->GetAnimator()->Play(L"ATK", false);
}


void AtkState::Update()
{
	if (GetMonster()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
}


void AtkState::Exit()
{
}