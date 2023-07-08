#include "pch.h"
#include "IdleState.h"
#include "PlayerMgr.h"

#include "CPlayer.h"
#include "CMonster.h"

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
	Vec2 vPlayerPos = pPlayer->GetLocalPos();

	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetLocalPos();

	// �÷��̾ ������ �νĹ��� ���η� ����
	if (Vec2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().recogRange)
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

