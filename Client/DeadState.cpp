#include "pch.h"
#include "DeadState.h"

// Include GameObject Header
#include "Monster.h"
#include "Player.h"

// Include Components Header
#include "CAnimator.h"
#include "CAnimation.h"

// Include Manager Header
#include "PlayerMgr.h"


DeadState::DeadState()
	: CState(MONSTER_STATE::DEAD)
{
}


DeadState::~DeadState()
{
}


void DeadState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"DEAD", false);
	PlayerMgr::GetI()->GetPlayer()->AddExp(2.f);
}


void DeadState::Update()
{
	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(GetOwner());
	}
}


void DeadState::Exit()
{
}