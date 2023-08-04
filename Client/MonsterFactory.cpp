#include "pch.h"
#include "MonsterFactory.h"

#include "Monster.h"
#include "Boss.h"
#include "AI.h"

// Include Components
#include "RigidBody.h"

// Include Monster State
#include "IdleState.h"
#include "TraceState.h"
#include "DeadState.h"
#include "AtkState.h"
// Include Boss State
#include "BTraceState.h"


#include "CCollider.h"


Monster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vect2 pos)
{


	switch (type)
	{
	case MONSTER_TYPE::NORMAL:
	{
		Monster* pMonster = new Monster(L"2");
		pMonster->SetPos(pos);
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);
		pMonster->CreateRigidBody();
		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f;
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
		return pMonster;
	}
	break;
	case MONSTER_TYPE::BOSS:
	{
		Boss* pMonster = new Boss(L"2");
		pMonster->SetName(L"Boss");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 50.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 5000.f;
		info.speed = 100.f;

		pMonster->setMonsterInfo(info);
		pMonster->SetScale(Vect2(300.f, 200.f));
		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new BTraceState);
		pAI->SetCurState(MONSTER_STATE::TRACE);

		pMonster->SetAI(pAI);
		return pMonster;
	}
	break;
	}

	

}
