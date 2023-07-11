#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{

	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {  };
		info.mfAtt = 10.f;
		info.mfAttRange = 50.f;
		info.mfDetectRange = 300.f;
		info.mfHp = 100.f;
		info.mfSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);
		/*AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);*/
	}

	break;

	case MON_TYPE::RANGE:

		break;
	default:
		break;
	}


	assert(pMon);

	return pMon;
}