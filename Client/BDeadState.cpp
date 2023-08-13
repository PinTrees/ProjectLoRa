#include "pch.h"
#include "CState.cpp"

#include "BDeadState.h"

// Include GameObject Header
#include "Monster.h"
#include "Player.h"
#include "Gold.h"
#include "Box.h"

#include "Random.h"

// Include Components Header
#include "CAnimator.h"
#include "CAnimation.h"

// Include Manager Header
#include "PlayerMgr.h"


BDeadState::BDeadState()
	: CState(MONSTER_STATE::DEAD)
{
}


BDeadState::~BDeadState()
{
}


void BDeadState::Enter()
{
	//Vect2 vOwnerPos = GetOwner()->GetLocalPos();
	//Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	//GetOwner()->GetAnimator()->Play(vOwnerPos.x > vPlayerPos.x ? L"DEAD_L" : L"DEAD_R", false);

	//PlayerMgr::GetI()->GetPlayer()->AddExp(2.f);
}


void BDeadState::Update()
{
	//if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	//{
	//	DeleteObject(GetOwner());

	//	if (CRandom::GetI()->Next(0, 100) < 80)
	//	{
	//		Gold* pGold = new Gold;
	//		pGold->SetPos(GetOwner()->GetLocalPos());
	//		CreateObject(pGold, GROUP_TYPE::GOLD);
	//	}
	//	else if (CRandom::GetI()->Next(0, 100) < 4)
	//	{
	//		Box* pBox = new Box;
	//		pBox->SetPos(GetOwner()->GetLocalPos());
	//		CreateObject(pBox, GROUP_TYPE::GOLD);
	//	}
	//}
}


void BDeadState::Exit()
{
}