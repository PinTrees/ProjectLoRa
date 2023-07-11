#include "pch.h"
#include "CState.h"

#include "AI.h"




CState::CState(MONSTER_STATE state)
	: mState(state)
	, mpAI(nullptr)
{
}


CState::~CState()
{
}


void CState::Enter()
{
}


void CState::Exit()
{
}


CMonster* CState::GetMonster()
{
	return mpAI->GetOwner();
}