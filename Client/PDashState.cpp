#include "pch.h"
#include "PDashState.h"

#include "CObject.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "Player.h"
#include "PlayerMgr.h"
#include "CCollider.h"
#include "Particle.h"


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

	mvDashDir = PlayerMgr::GetI()->GetPlayer()->GetDir();
	mvDashDir.Normalize();

	Particle* pEffect = new Particle(L"7");
	pEffect->SetPos(pPlayer->GetPos());
	CreateObject(pEffect, GROUP_TYPE::EFFECT);
}

void PDashState::Update()
{
	mDashTime += DT;

	Player* pPlayer = (Player*)GetOwner();

	Vect2 vPos = pPlayer->GetPos();
	Vect2 vTargetPos = vPos + mvDashDir * 250.f * mDashTime;

	if (mDashTime > 0.5f)
	{
		mDashTime = 0.f;
		pPlayer->SetPos(vTargetPos);
		CCamera::GetI()->SetLookAt(pPlayer->GetPos());
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);

		Particle* pEffect = new Particle(L"6");
		pEffect->SetPos(pPlayer->GetPos());
		CreateObject(pEffect, GROUP_TYPE::EFFECT);
	}
}

void PDashState::Exit()
{
	Player* pPlayer = (Player*)GetOwner();

	pPlayer->SetVisible(true);
	pPlayer->GetCollider()->SetActive(true);

	CCamera::GetI()->SetTarget(pPlayer);
}
