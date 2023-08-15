#include "pch.h"
#include "PRunState.h"

#include "CObject.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "Player.h"


PRunState::PRunState()
	: CState(PLAYER_STATE::RUN)
{
}

PRunState::~PRunState()
{
}


void PRunState::Enter()
{
}

void PRunState::Update()
{
	Player* pPlayer = (Player*)GetOwner();

	mvDir = pPlayer->GetDir().Normalize();
	pPlayer->SetPos(pPlayer->GetPos() + mvDir * 120.f * DT);
	pPlayer->SetFlip(mvDir.x < 1);

	pPlayer->GetAnimator()->Play(pPlayer->GetDir().x < 1 ? L"RUN_L" : L"RUN_R", true);
}

void PRunState::Exit()
{
}

