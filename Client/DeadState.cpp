#include "pch.h"
#include "DeadState.h"

#include "CMonster.h"

#include "CAnimator.h"
#include "CAnimation.h"


DeadState::DeadState()
	: CState(MONSTER_STATE::DEAD)
{
}


DeadState::~DeadState()
{
}


void DeadState::Enter()
{
	GetMonster()->GetAnimator()->Play(L"DEAD", false);
}


void DeadState::Update()
{
	if (GetMonster()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(GetMonster());
	}
}


void DeadState::Exit()
{
}