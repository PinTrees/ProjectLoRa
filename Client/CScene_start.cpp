#include "pch.h"
#include "CScene_start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CCamera.h"


CScene_start::CScene_start()
{
}

CScene_start::~CScene_start()
{
}

void CScene_start::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_HOLD(KEY::LBTN))
	{
		
		Vec2 vLookAt = CCamera::GetI()->GetRealPos(MOUSE_POS);
		CCamera::GetI()->SetLookAt(vLookAt);
	}
}

void CScene_start::Enter()
{



	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(640.f, 314.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

//	CCamera::GetI()->SetTarget(pObj);

	//몬스터 배치
	int iMonCount = 2;
	float fMoveDist = 125.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetI()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; i++)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정
	//  Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look 지정
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
}


//현재씬을 나갈때 실행되는 함수
void CScene_start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetI()->Reset();

}


