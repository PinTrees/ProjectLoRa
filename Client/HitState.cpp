#include "pch.h"
#include "HitState.h"

#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "PlayerMgr.h"
#include "Player.h"


HitState::HitState()
	: CState(MONSTER_STATE::HIT)
{
}

HitState::~HitState()
{
}


void HitState::Enter()
{
	Vect2 vOwnerPos = GetOwner()->GetLocalPos();
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	GetOwner()->GetAnimator()->Play(vOwnerPos.x > vPlayerPos.x ? L"HIT_L" : L"HIT_R", false);
}

void HitState::Update()
{
	if(GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
}



void HitState::Exit()
{
}

