#include "pch.h"
#include "MonsterFactory.h"

<<<<<<< Updated upstream
#include "CMonster.h"
=======
#include "Monster.h"
>>>>>>> Stashed changes
#include "AI.h"

// Include Components
#include "RigidBody.h"

// Include Monster State
#include "IdleState.h"
#include "TraceState.h"
#include "DeadState.h"
#include "AtkState.h"




<<<<<<< Updated upstream
CMonster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vec2 pos)
{
	CMonster* pMonster = nullptr;
=======
Monster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vect2 pos)
{
	Monster* pMonster = new Monster;

	pMonster->SetPos(pos);
	pMonster->CreateRigidBody();
>>>>>>> Stashed changes

	switch (type)
	{
	case MONSTER_TYPE::NORMAL:
	{
<<<<<<< Updated upstream
		pMonster = new CMonster;
		pMonster->SetPos(pos);

=======
>>>>>>> Stashed changes
		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.curHp = info.hp = 100.f;
		info.speed = 70.f;

		pMonster->setMonsterInfo(info);
<<<<<<< Updated upstream
		
		pMonster->CreateRigidBody();
		pMonster->GetRigidBody()->SetMess(1.f);

		AI* pAI = new AI;	
=======
		pMonster->GetRigidBody()->SetMess(1.f);

		AI<MONSTER_STATE>* pAI = new AI<MONSTER_STATE>;
>>>>>>> Stashed changes
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->AddState(new DeadState);
		pAI->AddState(new AtkState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
		break;
	case MONSTER_TYPE::BOSS:
<<<<<<< Updated upstream
=======
	{
	}
>>>>>>> Stashed changes
		break;
	}

	assert(pMonster);

    return pMonster;
}
