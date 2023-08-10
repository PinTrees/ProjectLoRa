#include "pch.h"
#include "CScene_start.h"

#include "CObject.h"
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
#include "CResMgr.h"
#include "Random.h"

// ==========================
// Game Manager Header
#include "PlayerMgr.h"
#include "TileMapMgr.h"
#include "SkillMgr.h"
#include "DatabaseMgr.h"

// UI Manager Header
#include "HubUIMgr.h"
#include "LevelUpUIMgr.h"
#include "GUIMgr.h"

// Path Manager Header
#include "AstarMgr.h"
#include "JPSMgr.h"
// ==========================


// Components Header
#include "CCollider.h"
#include "CTexture.h"
#include "CCamera.h"


// Player State Header
#include "AI.h"
#include "PIdleState.h"
#include "PRunState.h"
#include "PDashState.h"
#include "PAtkState.h"
#include "PDieState.h"

#include "MonsterFactory.h"


// UI Components Header
#include "CBtnUI.h"
#include "CImageUI.h"
#include "Boss.h"



Scene_Start::Scene_Start()
	: mfMstrDelay(25.f)
	, mfCurDelay(30.f)
	, mBossDelay(60.f * 0.01f)
	, mCurBossDelay(0.f)
	, mbBossRespone(false)
	, mMonsterWave()
	, mTimer(0.f)
{
}

Scene_Start::~Scene_Start()
{
	// 싱글톤 메모리 해제
	LevelUpUIMgr::Dispose();
	PlayerMgr::Dispose();
	HubUIMgr::Dispose();
	SkillMgr::Dispose();
	DatabaseMgr::Dispose();
	AstarMgr::Dispose();
	JPSMgr::Dispose();
	TileMapMgr::Dispose();
	GUIMgr::Dispose();
}


void Scene_Start::Update()
{
	CScene::Update();

	UINT frmae = CTimeMgr::GetI()->GetFrame();
	GUIMgr::GetI()->SetFrameText(frmae);

	mTimer += DT;
	GUIMgr::GetI()->SetTimerText((UINT)mTimer);

	if (mbBossRespone)
		return;

	mfCurDelay += DT;
	mCurBossDelay += DT;

	if (mCurBossDelay > mBossDelay || KEY_TAP(KEY::E))
	{
		mbBossRespone = true;
		mCurBossDelay = 0.f;
		createBoss();
	}

	if (mfCurDelay > mfMstrDelay)
	{
		mfCurDelay = 0.f;
		CreateMonster();
	}
}

void Scene_Start::Enter()
{
	/// Init ------------------------
	mfMstrDelay = 25.f;
	mfCurDelay = 30.f;
	mBossDelay = 60.f * 7.f;
	mCurBossDelay = 0.f;
	mbBossRespone = false;
	mMonsterWave = 0;
	/// -----------------------------

	LoadTile(this, L"database\\map_1.tile");

	PlayerMgr::GetI()->Init();
	GUIMgr::GetI()->Init();
	LevelUpUIMgr::GetI()->Init();
	HubUIMgr::GetI()->Init();
	DatabaseMgr::GetI()->Init();
	JPSMgr::GetI()->Init();

	createPlayer();

	int iEnvCount = 150;
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
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_MONSTER, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::GROUND_PLAYER, GROUP_TYPE::MONSTER);

	// Camera Look 지정
	Vect2 vResolution = CCore::GetI()->GetResolution();
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
	CCamera::GetI()->FadeOut(0.1f);
	CCamera::GetI()->FadeIn(2.f);
}


//현재씬을 나갈때 실행되는 함수
void Scene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetI()->Reset();
	CCamera::GetI()->SetTarget(nullptr);
}





void Scene_Start::CreateMonster() // 몬스터 웨이브 생성
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	// 몬스터를 소환할 가장자리 위치 설정
	float edgeDistance = 100.f;				// 가장자리로부터의 거리

	float xPos = PlayerMgr::GetI()->GetPlayer()->GetPos().x - vResolution.x / 2.f;
	float yPos = PlayerMgr::GetI()->GetPlayer()->GetPos().y - vResolution.y / 2.f;

	int MonsterCount = 5 + (float)mMonsterWave * 0.5f;
	Vect2 vMonsterInterval = vResolution / MonsterCount;

	for (int i = 0; i < MonsterCount; ++i) // 화면의 끝에서 근거리 공격 몬스터를 생성 (4방면에서 생성됨)
	{
		Vect2 vCreatePos1 = Vect2(xPos - edgeDistance, yPos + vMonsterInterval.y * i);		// 좌측 화면에서 몬스터를 생성
		Monster* pShort = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vResolution.x + edgeDistance, yPos + vMonsterInterval.y * i);	// 우측 화면에서 몬스터를 생성
		Monster* pShort1 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort1, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vMonsterInterval.x * i, yPos - edgeDistance);			// 화면 상단에서 몬스터를 생성
		Monster* pShort2 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort2, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vMonsterInterval.x * i, yPos + vResolution.y + edgeDistance);	// 화면 하단에서 몬스터를 생성
		Monster* pShort3 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort3, GROUP_TYPE::MONSTER);
	}

	for (int i = 0; i < MonsterCount; ++i) // 화면의 끝에서 원거리 공격 몬스터를 생성 (4방면에서 생성됨)
	{
		Vect2 vCreatePos = Vect2(xPos - edgeDistance, yPos + vMonsterInterval.y * i);
		Monster* pLong = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		AddObject(pLong, GROUP_TYPE::MONSTER);

		vCreatePos = Vect2(xPos + vResolution.x + edgeDistance, yPos + vMonsterInterval.y * i);
		Monster* pLong2 = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		AddObject(pLong2, GROUP_TYPE::MONSTER);

		vCreatePos = Vect2(xPos + vMonsterInterval.x * i, yPos - edgeDistance);
		Monster* pLong3 = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		AddObject(pLong3, GROUP_TYPE::MONSTER);

		vCreatePos = Vect2(xPos + vMonsterInterval.x * i, yPos + vResolution.y + edgeDistance);
		Monster* pLong4 = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		AddObject(pLong4, GROUP_TYPE::MONSTER);
	}

	++mMonsterWave;	// 몬스터 웨이브의 진행 상태만큼 몬스터를 증가하기 위해 사용
}

void Scene_Start::createBoss()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	Vect2 vRandomPos = Vect2(rand() % (int)vResolution.x,
							 rand() % (int)vResolution.x);

	Vect2 vCreatePos = CCamera::GetI()->GetRealPos(vRandomPos);

	Boss* pBoss = new Boss(L"1");
	pBoss->SetPos(vCreatePos);
	CreateObject(pBoss, GROUP_TYPE::MONSTER);
}


void Scene_Start::createEnvi()
{
	int tileX = TileMapMgr::GetI()->GetTileMapSizeX();
	int tiley = TileMapMgr::GetI()->GetTileMapSizeY();

	int xPos = rand() % tileX;
	int yPos = rand() % tiley;

	Vect2 vPos = Vect2(xPos, yPos);
	Vect2 vTileScale = Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER);
	Vect2 vCreatePos = vPos * TILE_SIZE_RENDER + vTileScale * 0.5f;

	AstarMgr::GetI()->SetObstacleTile(xPos, yPos);
	JPSMgr::GetI()->SetCollisionTile(xPos, yPos);

	int rand = CRandom::GetI()->Next(3, 5);
	Environment* pEnvObj = new Environment(std::to_wstring(rand));

	pEnvObj->SetName(L"ENV");
	pEnvObj->SetPos(vCreatePos);
	pEnvObj->GetCollider()->SetTrigger(false);
	AddObject(pEnvObj, GROUP_TYPE::ENV);
}



void Scene_Start::createPlayer()
{
	int tileX = TileMapMgr::GetI()->GetTileMapSizeX();
	int tiley = TileMapMgr::GetI()->GetTileMapSizeY();

	Vect2 vMapScale = Vect2(tileX * TILE_SIZE_RENDER, tiley * TILE_SIZE_RENDER);

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(vMapScale * 0.5f);
	//pPlayer->GetCollider()->SetTrigger(false);
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	AI<PLAYER_STATE>* pAI = new AI<PLAYER_STATE>;

	pAI->AddState(new PIdleState);
	pAI->AddState(new PRunState);
	pAI->AddState(new PDashState);
	pAI->AddState(new PAtkState);
	pAI->AddState(new PDieState);
	pAI->SetCurState(PLAYER_STATE::IDLE);

	pPlayer->SetAI(pAI);

	CCamera::GetI()->SetFixedLookAt(vMapScale * 0.5f);
	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);
}










