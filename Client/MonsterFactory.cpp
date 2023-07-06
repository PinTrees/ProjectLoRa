#include "pch.h"
#include "MonsterFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "IdleState.h"
#include "TraceState.h"

CMonster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vec2 pos)
{
	CMonster* pMonster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::NORMAL:
	{
		pMonster = new CMonster;
		pMonster->SetPos(pos);

		tMonsterInfo info = {};
		info.atk = 10.f;
		info.atkRange = 50.f;
		info.recogRange = 10000.f;
		info.hp = 100.f;
		info.speed = 300.f;

		pMonster->setMonsterInfo(info);
		
		AI* pAI = new AI;
		pAI->AddState(new IdleState);
		pAI->AddState(new TraceState);
		pAI->SetCurState(MONSTER_STATE::IDLE);

		pMonster->SetAI(pAI);
	}
		break;
	case MONSTER_TYPE::BOSS:
		break;
	}

	assert(pMonster);

    return pMonster;
}
