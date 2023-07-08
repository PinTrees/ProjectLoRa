#include "pch.h"
#include "CState.h"

#include "CMonster.h"
#include "AI.h"


CState::CState(MON_STATE _eState)
	:meState(_eState)
{
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return mpAI->GetOwner();
}
