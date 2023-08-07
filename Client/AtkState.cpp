#include "pch.h"
#include "CState.cpp"

#include "PlayerMgr.h"
#include "CTimeMgr.h"

#include "AtkState.h"

// Components Header
#include "CAnimator.h"
#include "CAnimation.h"

#include "Player.h"
#include "Monster.h"
#include "Monster_Arrow.h"




AtkState::AtkState()
	: CState(MONSTER_STATE::ATTACK)
	, mAtkAvailable(true)
{
}


AtkState::~AtkState()
{
}


void AtkState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"ATK", false);
}


void AtkState::Update()
{
	Monster* monster = (Monster*)GetOwner();

	if (monster->GetType() == MONSTER_TYPE::SHORT)
	{

	}
	else if (monster->GetType() == MONSTER_TYPE::LONG				// ���Ÿ� ���� ������ �غ� �Ǹ� ����
		&& mAtkAvailable)											// bool ������ ����� ������ attack���¿��� ������ �������ϴ� ���� ���� ����
	{
		Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetPos();
		Vect2 Dir = vPlayer - monster->GetPos();
		Dir.Normalize();

		Monster_Arrow* arrow = new Monster_Arrow;

		arrow->SetPos(GetOwner()->GetPos());
		arrow->SetDir(Dir);
		arrow->SetOwner(monster);

		CreateObject(arrow, GROUP_TYPE::PROJ_MONSTER);
		mAtkAvailable = false;
	}

	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		mAtkAvailable = true;
	}
}


void AtkState::Exit()
{
}