#include "pch.h"
#include "HitState.h"

#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"



HitState::HitState()
	: CState(MONSTER_STATE::HIT)
{
}

HitState::~HitState()
{
}


void HitState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"HIT", false);
}

void HitState::Update()
{
	if(GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
}



void HitState::Exit()
{
}

