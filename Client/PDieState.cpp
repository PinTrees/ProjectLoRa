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
	, mDelay(1.f)
	, mCurDelay(0.f)
	, mbEnd(false)
{
}

PDieState::~PDieState()
{
}

void PDieState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();
	CCamera::GetI()->FadeOut(mDelay);
}


void PDieState::Update()
{
	if (mbEnd) return;

	mCurDelay += DT;

	if (mCurDelay >= mDelay)
	{
		mbEnd = true;
		mCurDelay = 0.f;
		GUIMgr::GetI()->ShowGameOverUI();
	}
}


void PDieState::Exit()
{
}
