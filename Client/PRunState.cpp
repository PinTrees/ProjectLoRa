#include "pch.h"
#include "PRunState.h"

#include "CObject.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "Player.h"
#include "Gun.h"


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

	mvDir = pPlayer->GetRunDir().Normalize();
	pPlayer->SetPos(pPlayer->GetPos() + mvDir * 180.f * DT);
	pPlayer->SetFlip(mvDir.x < 1);

	if (pPlayer->GetRunDir().x < 1)
	{
		pPlayer->GetAnimator()->Play(L"RUN_L", true);
	}
	else
	{
		pPlayer->GetAnimator()->Play(L"RUN_R", true);
	}
}

void PRunState::Exit()
{
}

