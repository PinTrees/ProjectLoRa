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
	: mfMstrDelay(5.f)
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
	// �̱��� �޸� ����
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

	mTimer += DT;
	GUIMgr::GetI()->SetTimerText((UINT)mTimer);
	GUIMgr::GetI()->SetFrameText(CTimeMgr::GetI()->GetFrame());

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
	mfMstrDelay = 5.f;
	mfCurDelay = 30.f;
	mBossDelay = 60.f * 7.f;
	mCurBossDelay = 0.f;
	mbBossRespone = false;
	mMonsterWave = 0;
	/// -----------------------------

	LoadTile(this, L"database\\map_1.tile");

	int mapX = TileMapMgr::GetI()->GetTileMapSizeX();
	int mapY = TileMapMgr::GetI()->GetTileMapSizeY();

	CScene::InitBSP(Vect2(mapX * TILE_SIZE_RENDER, mapY * TILE_SIZE_RENDER), 10, 10);


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

	// �浹 ����
	//  Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::GROUND_PLAYER);

	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::GROUND_PLAYER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PLAYER);

	//CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENV);

	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	//CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GOLD);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ENV);

	// Camera Look ����
	Vect2 vResolution = CCore::GetI()->GetResolution();
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
	CCamera::GetI()->FadeOut(0.1f);
	CCamera::GetI()->FadeIn(2.f);
}


//������� ������ ����Ǵ� �Լ�
void Scene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetI()->Reset();
	CCamera::GetI()->SetTarget(nullptr);
}





void Scene_Start::CreateMonster() // ���� ���̺� ����
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	// ���͸� ��ȯ�� �����ڸ� ��ġ ����
	float edgeDistance = 250.f;  // �����ڸ��κ����� �Ÿ�

	float xPos = PlayerMgr::GetI()->GetPlayer()->GetPos().x - vResolution.x * 0.5f;
	float yPos = PlayerMgr::GetI()->GetPlayer()->GetPos().y - vResolution.y * 0.5f;

	int MonsterCount = 10 + (float)mMonsterWave * 1.f;
	MonsterCount = MonsterCount > 100 ? 100 : MonsterCount;

	float ellipseWidth = vResolution.x + edgeDistance * 2.0f;  // Ÿ������ ���� ũ��
	float ellipseHeight = vResolution.y + edgeDistance * 2.0f; // Ÿ������ ���� ũ��

	Vect2 vCenter(xPos + vResolution.x * 0.5f, yPos + vResolution.y * 0.5f);


	for (int i = 0; i < MonsterCount; ++i) // ȭ���� ������ �ٰŸ� ���� ���͸� ���� (4��鿡�� ������)
	{
		float angle = i * (360.0f / MonsterCount) + 20.f;  // ������ ���

		float x = vCenter.x + (ellipseWidth * 0.45f) * cos(angle * PI / 180.0f);
		float y = vCenter.y - (ellipseHeight * 0.45f) * sin(angle * PI / 180.0f);

		Vect2 vCreatePos(x, y);
		 
		// ���� ���� �� �߰�
		Monster* pShort = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos);
		AddObject(pShort, GROUP_TYPE::MONSTER);
	}


	for (int i = 0; i < MonsterCount; ++i) // ȭ���� ������ �ٰŸ� ���� ���͸� ���� (4��鿡�� ������)
	{
		float angle = i * (360.0f / MonsterCount);  // ������ ���

		float x = vCenter.x + (ellipseWidth / 2.0f) * cos(angle * PI / 180.0f);
		float y = vCenter.y - (ellipseHeight / 2.0f) * sin(angle * PI / 180.0f);

		Vect2 vCreatePos(x, y);

		// ���� ���� �� �߰�
		Monster* pLong = MonsterFactory::CreateMonster(MONSTER_TYPE::LONG, vCreatePos);
		AddObject(pLong, GROUP_TYPE::MONSTER);
	}

	++mMonsterWave;	// ���� ���̺��� ���� ���¸�ŭ ���͸� �����ϱ� ���� ���
}

void Scene_Start::createBoss()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	Vect2 vRandomPos = Vect2(rand() % (int)vResolution.x,
							 rand() % (int)vResolution.x);

	Vect2 vCreatePos = CCamera::GetI()->GetRealPos(vRandomPos);

	Boss* pBoss = (Boss*)MonsterFactory::CreateMonster(MONSTER_TYPE::BOSS, vCreatePos);
	CreateObject(pBoss, GROUP_TYPE::BOSS);
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










