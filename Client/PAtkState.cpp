#include "pch.h"
#include "PAtkState.h"

#include "CKeyMgr.h"
#include "Player.h"
#include "Gun.h"

#include "CAnimator.h"
#include "CAnimation.h"




PAtkState::PAtkState()
	: CState(PLAYER_STATE::ATTACK)
{
}

PAtkState::~PAtkState()
{
}



void PAtkState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();
	Vect2 pos = CCamera::GetI()->GetRealPos(MOUSE_POS);
	pPlayer->GetAnimator()->Play(pos.x > pPlayer->GetLocalPos().x ? L"ATK_R" : L"ATK_L", false);

	int count = pPlayer->GetCurGun()->GetInfo().shotCount;
	for (int i = 0; i < count; ++i)
	{
		pPlayer->GetCurGun()->Shot();
	}
}

void PAtkState::Update()
{
	Player* pPlayer = (Player*)GetOwner();

	if (pPlayer->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void PAtkState::Exit()
{
}

