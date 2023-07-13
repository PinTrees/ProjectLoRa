#include "pch.h"
#include "IdleState.h"
<<<<<<< Updated upstream
#include "PlayerMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
=======

#include "PlayerMgr.h"

#include "Player.h"
#include "Monster.h"

>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	Vec2 vPlayerPos = pPlayer->GetLocalPos();

	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetLocalPos();

	// �÷��̾ ������ �νĹ��� ���η� ����
	if (Vec2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().recogRange)
=======
	Vect2 vPlayerPos = pPlayer->GetLocalPos();

	Monster* pMonster = (Monster*)GetOwner();
	Vect2 vMonsterPos = pMonster->GetLocalPos();

	// �÷��̾ ������ �νĹ��� ���η� ����
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().recogRange)
>>>>>>> Stashed changes
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

