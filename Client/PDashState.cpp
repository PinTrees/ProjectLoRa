#include "pch.h"
#include "PDashState.h"

#include "CObject.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "Player.h"


PDashState::PDashState()
	: CState(PLAYER_STATE::DASH)
{
}

PDashState::~PDashState()
{
}



void PDashState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();

	pPlayer->GetAnimator()->Play(L"DASH_R", false);

	mvDashDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - pPlayer->GetPos();
	mvDashDir.Normalize();
}

void PDashState::Update()
{
	Player* pPlayer = (Player*)GetOwner();

	Vect2 vPos = pPlayer->GetPos();
	pPlayer->SetPos(vPos + mvDashDir * 700.f * DT);

	if (pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void PDashState::Exit()
{
	Player* pPlayer = (Player*)GetOwner();
}
