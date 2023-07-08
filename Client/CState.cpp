#include "pch.h"
#include "CState.h"




void CState::Enter()
{
}

void CState::Exit()
{
}

CState::CState(MONSTER_STATE state)
	: mState(state)
	, mpAI(nullptr)
{
}

CState::~CState()
{
}
