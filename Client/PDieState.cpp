#include "pch.h"
#include "PDieState.h"

#include "PlayerMgr.h"

#include "Player.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CCamera.h"
#include "CTimeMgr.h"

#include "GUIMgr.h"




PDieState::PDieState()
	: CState(PLAYER_STATE::DIE)
{
}

PDieState::~PDieState()
{
}

void PDieState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();
	GUIMgr::GetI()->ShowGameOverUI();
}


void PDieState::Update()
{
}


void PDieState::Exit()
{
}
