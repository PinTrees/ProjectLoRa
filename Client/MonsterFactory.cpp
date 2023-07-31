#include "pch.h"
#include "MonsterFactory.h"

#include "Monster.h"
#include "AI.h"

// Include Components
#include "RigidBody.h"

// Include Monster State
#include "IdleState.h"
#include "TraceState.h"
#include "DeadState.h"
#include "AtkState.h"

#include "CCollider.h"


int MonsterFactory::mCreateCount = 0;


Monster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vect2 pos)
{
	Monster* pMonster = new Monster(L"2");

	pMonster->SetPos(pos);
	pMonster->CreateRigidBody();
	pMonster->SetName(L"Monster");
	pMonster->GetCollider()->SetTrigger(false);

	switch (type)
	{
	case MONSTER_TYPE::NORMAL:
	{
		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f * pow(1.002f, mCreateCount);
		info.speed = 70.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
		break;
	case MONSTER_TYPE::BOSS:
	{
	}
		break;
	}

	assert(pMonster);

	++mCreateCount;
    return pMonster;
}
