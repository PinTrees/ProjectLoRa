#include "pch.h"
#include "DeadState.h"

#include "CMonster.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

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
	GetMonster()->GetAnimator()->Play(L"DEAD", false);
	PlayerMgr::GetI()->GetPlayer()->AddExp(2.f);
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