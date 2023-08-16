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

#include "Boss.h"
#include "BSkillAtkState.h"
#include "BTraceState.h"
#include "BDeadState.h"

#include "CCollider.h"
#include "WaveMgr.h"


int MonsterFactory::mCreateCount = 0;


Monster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vect2 pos)
{
	Monster* pMonster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::ELITE:
	{
		pMonster = new Monster(type, L"6");

		pMonster->SetPos(pos);
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 15.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 200.f + 30 * WaveMgr::GetI()->GetCurWaveCount();
		info.speed = 120.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->AddState(new HitState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
	break;
	case MONSTER_TYPE::SHORT:
	{
		pMonster = new Monster(type, L"4");

		pMonster->SetPos(pos);
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 7.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f + 30 * WaveMgr::GetI()->GetCurWaveCount();
		info.speed = 60.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->AddState(new HitState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
	break;
	case MONSTER_TYPE::LONG: 
	{
		pMonster = new Monster(type, L"3");

		pMonster->SetPos(pos); 
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 5.f;
		info.atkRange = 250.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 50.f + 20 * WaveMgr::GetI()->GetCurWaveCount();
		info.speed = 20.f;
		info.atkSpeed = 3.f;

		pMonster->setMonsterInfo(info);
		pMonster->GetRigidBody()->SetMess(1.f);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->AddState(new HitState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
	break;
	case MONSTER_TYPE::LOCK:
	{
		pMonster = new Monster(type, L"5");

		pMonster->SetPos(pos);
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);

		tMonsterInfo info = {};
		info.atk = 5.f;
		info.atkRange = 250.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 750.f * 100 * WaveMgr::GetI()->GetCurWaveCount();
		info.atkSpeed = 3.f;
		info.speed = 25.f;

		pMonster->setMonsterInfo(info);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->AddState(new HitState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
	break;
	case MONSTER_TYPE::BOSS:
	{
		pMonster = new Boss(L"2");
		pMonster->SetName(L"Monster");
		pMonster->GetCollider()->SetTrigger(false);
		pMonster->SetPos(pos);

		tMonsterInfo info = {};
		info.atk = 50.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 1000000.f;
		info.speed = 100.f;
		pMonster->setMonsterInfo(info);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
		pAI->AddState(new BTraceState);
		pAI->AddState(new BSkillAtkState);
		pAI->AddState(new BDeadState);
		pAI->SetCurState(MONSTER_STATE::TRACE);

		pMonster->SetAI(pAI);
	}
	break;
	}

	assert(pMonster);

	++mCreateCount;
	return pMonster;
}
