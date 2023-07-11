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


CObject* CState::GetOwner()
{
	return mpAI->GetOwner();
}