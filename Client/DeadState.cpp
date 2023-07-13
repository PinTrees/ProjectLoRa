#include "pch.h"
<<<<<<< Updated upstream
#include "DeadState.h"

#include "CMonster.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

=======
#include "CState.cpp"

#include "DeadState.h"

// Include GameObject Header
#include "Monster.h"
#include "Player.h"
#include "Gold.h"

// Include Components Header
#include "CAnimator.h"
#include "CAnimation.h"

// Include Manager Header
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	GetMonster()->GetAnimator()->Play(L"DEAD", false);
=======
	GetOwner()->GetAnimator()->Play(L"DEAD", false);
>>>>>>> Stashed changes
	PlayerMgr::GetI()->GetPlayer()->AddExp(2.f);
}


void DeadState::Update()
{
<<<<<<< Updated upstream
	if (GetMonster()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(GetMonster());
=======
	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(GetOwner());

		Gold* pGold = new Gold;
		pGold->SetPos(GetOwner()->GetLocalPos());
		pGold->SetScale(Vect2(36.f, 36.f));
		CreateObject(pGold, GROUP_TYPE::GOLD);
>>>>>>> Stashed changes
	}
}


void DeadState::Exit()
{
}