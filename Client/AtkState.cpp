#include "pch.h"
<<<<<<< Updated upstream
#include "AtkState.h"

#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"

=======
#include "CState.cpp"

#include "AtkState.h"

// Components Header
#include "CAnimator.h"
#include "CAnimation.h"

#include "Monster.h"

>>>>>>> Stashed changes



AtkState::AtkState()
	: CState(MONSTER_STATE::ATTACK)
{
}


AtkState::~AtkState()
{
}


void AtkState::Enter()
{
<<<<<<< Updated upstream
	GetMonster()->GetAnimator()->Play(L"ATK", false);
=======
	GetOwner()->GetAnimator()->Play(L"ATK", false);
>>>>>>> Stashed changes
}


void AtkState::Update()
{
<<<<<<< Updated upstream
	if (GetMonster()->GetAnimator()->GetCurAnimation()->IsFinish())
=======
	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
>>>>>>> Stashed changes
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
}


void AtkState::Exit()
{
}