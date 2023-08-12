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
#include "HitState.h"

#include "CCollider.h"


int MonsterFactory::mCreateCount = 0;


Monster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vect2 pos)
{
	Monster* pMonster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::SHORT:
	{
		pMonster = new Monster(type, L"4");

		pMonster->SetPos(pos);
		pMonster->CreateRigidBody();
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 7.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 200.f * pow(1.001f, mCreateCount);
		info.speed = 65.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);
	}
	break;
	case MONSTER_TYPE::LONG: 
	{
		pMonster = new Monster(type, L"3");

		pMonster->SetPos(pos); 
		pMonster->CreateRigidBody();
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 5.f;
		info.atkRange = 250.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 150.f * pow(1.001f, mCreateCount);
		info.speed = 45.f;
		info.atkSpeed = 3.f;

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
	pAI->AddState(new HitState);
	pAI->SetCurState(MONSTER_STATE::IDLE);

	pMonster->SetAI(pAI);

	assert(pMonster);

	++mCreateCount;
	return pMonster;
}
