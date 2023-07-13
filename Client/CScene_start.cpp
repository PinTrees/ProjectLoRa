#include "pch.h"
#include "CScene_start.h"

#include "CObject.h"
<<<<<<< Updated upstream

#include "CPlayer.h"
#include "CMonster.h"
#include "Environment.h"

=======
>>>>>>> Stashed changes
#include "CCore.h"

// GameObject Header
#include "Environment.h"
#include "Monster.h"
#include "Player.h"

// System Manager Header
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"

<<<<<<< Updated upstream
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CCollider.h"

#include "MonsterFactory.h"
#include "PlayerMgr.h"
=======
// Manager Header
#include "PlayerMgr.h"

// Components Header
#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"

#include "AI.h"
#include "PIdleState.h"

#include "MonsterFactory.h"



>>>>>>> Stashed changes

Scene_Start::Scene_Start()
	: mfMstrDelay(1.f)
	, mfCurDelay(0.f)
{
}

Scene_Start::~Scene_Start()
{
}



void Scene_Start::Update()
{
	CScene::Update();
<<<<<<< Updated upstream

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_HOLD(KEY::LBTN)) 
	{
		
		Vec2 vLookAt = CCamera::GetI()->GetRealPos(MOUSE_POS);
		CCamera::GetI()->SetLookAt(vLookAt);
	}

	mfCurDelay += DT;
	if (mfCurDelay > mfMstrDelay)
	{
		mfCurDelay = 0.f;
		CreateMonster();
	}
}

void Scene_Start::Enter()
{
	LoadTile(this, L"database\\map_1.tile");

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(Vec2(640.f, 384.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);
=======

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	mfCurDelay += DT;
	if (mfCurDelay > mfMstrDelay)
	{
		mfCurDelay = 0.f;
		CreateMonster();
	}
}

void Scene_Start::Enter()
{
	LoadTile(this, L"database\\map_1.tile");

	
>>>>>>> Stashed changes

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(Vect2(640.f, 384.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	AI<PLAYER_STATE>* pAI = new AI<PLAYER_STATE>;
	pAI->AddState(new PIdleState);
	pAI->SetCurState(PLAYER_STATE::IDLE);

	pPlayer->SetAI(pAI);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);

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
<<<<<<< Updated upstream
	Vec2 vResolution = CCore::GetI()->GetResolution();
=======
	Vect2 vResolution = CCore::GetI()->GetResolution();
>>>>>>> Stashed changes
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
	CCamera::GetI()->FadeOut(2.f);
	CCamera::GetI()->FadeIn(2.f);
}


//현재씬을 나갈때 실행되는 함수
void Scene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetI()->Reset();
	CCamera::GetI()->SetTarget(nullptr);
}





void Scene_Start::CreateMonster()
{
<<<<<<< Updated upstream
	Vec2 vResolution = CCore::GetI()->GetResolution();
=======
	Vect2 vResolution = CCore::GetI()->GetResolution();
>>>>>>> Stashed changes

	// 몬스터를 소환할 가장자리 위치 설정
	float edgeDistance = 100.f;				// 가장자리로부터의 거리
	float xPos = rand() % (int)(vResolution.x - 2 * edgeDistance) + edgeDistance; // x 좌표 범위: edgeDistance부터 (가로 해상도 - 2 * edgeDistance)까지
	float yPos = rand() % (int)(vResolution.y - 2 * edgeDistance) + edgeDistance; // y 좌표 범위: edgeDistance부터 (세로 해상도 - 2 * edgeDistance)까지

<<<<<<< Updated upstream
	Vec2 vCreatePos;
	// 가장자리 위치 계산
	// 상하 가장자리
	if (rand() % 2 == 0) 
		vCreatePos = Vec2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	// 좌우 가장자리
	else 
		vCreatePos = Vec2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
=======
	Vect2 vCreatePos;
	// 가장자리 위치 계산
	// 상하 가장자리
	if (rand() % 2 == 0) 
		vCreatePos = Vect2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	// 좌우 가장자리
	else 
		vCreatePos = Vect2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
>>>>>>> Stashed changes
	
	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);


<<<<<<< Updated upstream
	CMonster* pMonsterObj = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vCreatePos);
	pMonsterObj->SetName(L"Monster");
	pMonsterObj->SetScale(Vec2(280.f, 180.f));
=======
	Monster* pMonsterObj = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vCreatePos);
	pMonsterObj->SetName(L"Monster");
	pMonsterObj->SetScale(Vect2(280.f, 180.f));
>>>>>>> Stashed changes
	pMonsterObj->GetCollider()->SetTrigger(false);

	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
}




void Scene_Start::createEnvi()
{
<<<<<<< Updated upstream
	Vec2 vResolution = CCore::GetI()->GetResolution();

	float xPos = rand() % (int)(vResolution.x);
	float yPos = rand() % (int)(vResolution.y); 
	Vec2 vCreatePos = Vec2(xPos, yPos);
=======
	Vect2 vResolution = CCore::GetI()->GetResolution();

	float xPos = rand() % (int)(vResolution.x);
	float yPos = rand() % (int)(vResolution.y); 
	Vect2 vCreatePos = Vect2(xPos, yPos);
>>>>>>> Stashed changes

	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);

	Environment* pEnvObj = nullptr;
	pEnvObj = new Environment(L"101");
	pEnvObj->SetName(L"ENV");
	pEnvObj->SetPos(vCreatePos);
	pEnvObj->GetCollider()->SetTrigger(false);
	AddObject(pEnvObj, GROUP_TYPE::ENV);
}



