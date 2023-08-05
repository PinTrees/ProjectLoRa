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
	Monster* pMonster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::SHORT:
	{
		pMonster = new Monster(type, L"2");

		pMonster->SetPos(pos);
		pMonster->CreateRigidBody();
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f * pow(1.002f, mCreateCount);
		info.speed = 70.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);
	}
		break;
	case MONSTER_TYPE::LONG:
	{
		pMonster = new Monster(type, L"1");

		pMonster->SetPos(pos);
		pMonster->CreateRigidBody();
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 350.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f * pow(1.002f, mCreateCount);
		info.speed = 10.f;
		info.atkSpeed = 2.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);
	}
		break;
	}

	AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
	pAI->AddState(new IdleState);
	pAI->AddState(new TraceState);
	pAI->AddState(new DeadState);
	pAI->AddState(new AtkState);
	pAI->SetCurState(MONSTER_STATE::IDLE);

	pMonster->SetAI(pAI);

	assert(pMonster);

	++mCreateCount;
    return pMonster;
}
