#include "pch.h"
#include "CScene_start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"


CScene_start::CScene_start()
{
}

CScene_start::~CScene_start()
{
}

void CScene_start::Enter()
{ 



	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);
	

	//몬스터 배치
	int iMonCount = 5;
	float fMoveDist = 125.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetI()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist +fObjScale/2.f)*2)) / (float)(iMonCount -1);

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; i++)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i* fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}

}

void CScene_start::Exit()
{
}


