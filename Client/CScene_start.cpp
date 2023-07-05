#include "pch.h"
#include "CScene_start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "Environment.h"

#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CCollider.h"


CScene_start::CScene_start()
	: mfMstrDelay(1.f)
	, mfCurDelay(0.f)
	, mPlayer(nullptr)
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

	mfCurDelay += fDT;
	if (mfCurDelay > mfMstrDelay)
	{
		mfCurDelay = 0.f;
		CreateMonster();
	}
}

void CScene_start::Enter()
{

	/*Environment* pBackObj = new Environment(L"back_1");
	pBackObj->SetName(L"BACK");
	pBackObj->SetScale(Vec2(1800.f, 1800.f));
	pBackObj->SetPos(Vec2(CCore::GetI()->GetResolution()) * 0.5f);
	AddObject(pBackObj, GROUP_TYPE::BACK);*/

	for (int i = 0; i < 20; ++i)
	{
		for (int y = 0; y < 20; ++y)
		{
			Environment* pBackObj = new Environment(L"back_1");
			pBackObj->SetName(L"BACK");
			pBackObj->SetScale(Vec2(250.f, 250.f));
			pBackObj->SetPos(pBackObj->GetScale() * Vec2(i, y));
			AddObject(pBackObj, GROUP_TYPE::BACK);
		}
	}


	mPlayer = new CPlayer;
	mPlayer->SetName(L"Player");
	mPlayer->SetPos(Vec2(640.f, 384.f));
	AddObject(mPlayer, GROUP_TYPE::PLAYER);

	CCamera::GetI()->SetTarget(mPlayer);

	//몬스터 배치
	int iMonCount = 8;
	for (int i = 0; i < iMonCount; i++)
	{
		CreateMonster();
	}


	


	int iEnvCount = 8;
	for (int i = 0; i < iEnvCount; i++)
	{
		createEnvi();
	}


	// 충돌 지정
	//  Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GOLD);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ENV);

	// Camera Look 지정
	Vec2 vResolution = CCore::GetI()->GetResolution();
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
}


//현재씬을 나갈때 실행되는 함수
void CScene_start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetI()->Reset();
}





void CScene_start::CreateMonster()
{
	Vec2 vResolution = CCore::GetI()->GetResolution();
	Vec2 vCreatePos;

	// 몬스터를 소환할 가장자리 위치 설정
	float edgeDistance = 100.f; // 가장자리로부터의 거리
	float xPos = rand() % (int)(vResolution.x - 2 * edgeDistance) + edgeDistance; // x 좌표 범위: edgeDistance부터 (가로 해상도 - 2 * edgeDistance)까지
	float yPos = rand() % (int)(vResolution.y - 2 * edgeDistance) + edgeDistance; // y 좌표 범위: edgeDistance부터 (세로 해상도 - 2 * edgeDistance)까지

	// 가장자리 위치 계산
	if (rand() % 2 == 0) // 상하 가장자리
	{
		vCreatePos = Vec2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	}
	else // 좌우 가장자리
	{
		vCreatePos = Vec2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
	}

	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);

	CMonster* pMonsterObj = nullptr;
	pMonsterObj = new CMonster;
	pMonsterObj->SetName(L"Monster");
	pMonsterObj->SetMoveDistance(100.f);
	pMonsterObj->SetPos(vCreatePos);
	pMonsterObj->SetCenterPos(Vec2(0.f, 0.f));
	pMonsterObj->SetScale(Vec2(280.f, 180.f));
	pMonsterObj->SetTarget(mPlayer);
	pMonsterObj->GetCollider()->SetTrigger(false);
	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
}




void CScene_start::createEnvi()
{
	Vec2 vResolution = CCore::GetI()->GetResolution();

	float xPos = rand() % (int)(vResolution.x);
	float yPos = rand() % (int)(vResolution.y); 
	Vec2 vCreatePos = Vec2(xPos, yPos);

	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);

	Environment* pEnvObj = nullptr;
	pEnvObj = new Environment(L"101");
	pEnvObj->SetName(L"ENV");
	pEnvObj->SetPos(vCreatePos);
	pEnvObj->GetCollider()->SetTrigger(false);
	AddObject(pEnvObj, GROUP_TYPE::ENV);
}



