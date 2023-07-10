#include "pch.h"
#include "IdleState.h"

#include "PlayerMgr.h"

#include "Player.h"
#include "Monster.h"


IdleState::IdleState()
	: CState(MONSTER_STATE::IDLE)
{
}


IdleState::~IdleState()
{
}


void IdleState::Update()
{
	// �÷��̾���� �Ÿ� Ȯ��
	// ���� ������ ���Խ� ����
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
	Vect2 vPlayerPos = pPlayer->GetLocalPos();

	Monster* pMonster = (Monster*)GetOwner();
	Vect2 vMonsterPos = pMonster->GetLocalPos();

	// �÷��̾ ������ �νĹ��� ���η� ����
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().recogRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}
}


void IdleState::Enter()
{
}


void IdleState::Exit()
{
}

