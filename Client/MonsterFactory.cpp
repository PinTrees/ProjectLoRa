#include "pch.h"
#include "MonsterFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "IdleState.h"
#include "TraceState.h"
#include "CHP.h"

CMonster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vec2 pos)
{
	CMonster* pMonster = nullptr;

	switch (type)
	{
	case MONSTER_TYPE::NORMAL:
	{
		pMonster = new CMonster;
		pMonster->SetPos(pos);
		pMonster->SetName(L"Monster");
		pMonster->SetFullHP(300.f);
		pMonster->GetHPbar()->SetOffset(Vec2(40.f, -35.f));
		pMonster->GetHPbar()->SetSize(Vec2(60.f, 5.f));

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
