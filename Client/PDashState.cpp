#include "pch.h"
#include "PDashState.h"

#include "CObject.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CKeyMgr.h"
#include "PlayerMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "Player.h"


PDashState::PDashState()
	: CState(PLAYER_STATE::DASH)
	, mDashTime()
{
}

PDashState::~PDashState()
{
}



void PDashState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();

	pPlayer->GetAnimator()->Play(L"DASH_R", false);
	pPlayer->SetVisible(false);
	pPlayer->GetCollider()->SetActive(false);

	CCamera::GetI()->SetTarget(nullptr);
	mvDashDir = PlayerMgr::GetI()->GetPlayer()->GetRunDir();
	mvDashDir.Normalize();
}

void PDashState::Update()
{
	mDashTime += DT;

	Player* pPlayer = (Player*)GetOwner();

	Vect2 vPos = pPlayer->GetPos();
	pPlayer->SetPos(vPos + mvDashDir * 300.f * DT);

	if (mDashTime > 0.5f)
	{
		mDashTime = 0.f;
		CCamera::GetI()->SetLookAt(vPos);
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void PDashState::Exit()
{
	Player* pPlayer = (Player*)GetOwner();
	pPlayer->SetVisible(true);
	pPlayer->GetCollider()->SetActive(true);

	CCamera::GetI()->SetTarget(pPlayer);
}
