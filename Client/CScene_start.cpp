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



Scene_Start::Scene_Start()
	: mfMstrDelay(30.f)
	, mfCurDelay(30.f)
	, mMonsterWave()
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

	mfCurDelay += DT;

	if (mfCurDelay > mfMstrDelay)
	{
		mfCurDelay = 0.f;
		CreateMonster();
	}

	UINT frmae = CTimeMgr::GetI()->GetFrame();
	GUIMgr::GetI()->SetFrameText(frmae);
}

void Scene_Start::Enter()
{
	LoadTile(this, L"database\\map_1.tile");

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
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GOLD);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_MONSTER, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::GROUND_PLAYER, GROUP_TYPE::MONSTER);

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
	float edgeDistance = 100.f;				// �����ڸ��κ����� �Ÿ�

	float xPos = PlayerMgr::GetI()->GetPlayer()->GetPos().x - vResolution.x / 2.f;
	float yPos = PlayerMgr::GetI()->GetPlayer()->GetPos().y - vResolution.y / 2.f;

	int MonsterCount = 5 + (float)mMonsterWave * 3.f;
	Vect2 vMonsterInterval = vResolution / MonsterCount;

	for (int i = 0; i < MonsterCount; ++i) // ȭ���� ������ �ٰŸ� ���� ���͸� ���� (4��鿡�� ������)
	{
		Vect2 vCreatePos1 = Vect2(xPos - edgeDistance, yPos + vMonsterInterval.y * i);		// ���� ȭ�鿡�� ���͸� ����
		Monster* pShort = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vResolution.x + edgeDistance, yPos + vMonsterInterval.y * i);	// ���� ȭ�鿡�� ���͸� ����
		Monster* pShort1 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort1, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vMonsterInterval.x * i, yPos - edgeDistance);			// ȭ�� ��ܿ��� ���͸� ����
		Monster* pShort2 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort2, GROUP_TYPE::MONSTER);

		vCreatePos1 = Vect2(xPos + vMonsterInterval.x * i, yPos + vResolution.y + edgeDistance);	// ȭ�� �ϴܿ��� ���͸� ����
		Monster* pShort3 = MonsterFactory::CreateMonster(MONSTER_TYPE::SHORT, vCreatePos1);
		AddObject(pShort3, GROUP_TYPE::MONSTER);
	}

	for (int i = 0; i < MonsterCount; ++i) // ȭ���� ������ ���Ÿ� ���� ���͸� ���� (4��鿡�� ������)
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

	++mMonsterWave;	// ���� ���̺��� ���� ���¸�ŭ ���͸� �����ϱ� ���� ���
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

	Environment* pEnvObj = new Environment(L"101");

	pEnvObj->SetName(L"ENV");
	pEnvObj->SetPos(vCreatePos);
	pEnvObj->SetScale(vTileScale);
	pEnvObj->GetCollider()->SetScale(vTileScale);
	pEnvObj->GetCollider()->SetTrigger(false);
	AddObject(pEnvObj, GROUP_TYPE::ENV);
}



void Scene_Start::createPlayer()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(vResolution * 0.5f);
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	AI<PLAYER_STATE>* pAI = new AI<PLAYER_STATE>;

	pAI->AddState(new PIdleState);
	pAI->AddState(new PRunState);
	pAI->AddState(new PDashState);
	pAI->AddState(new PAtkState);
	pAI->AddState(new PDieState);
	pAI->SetCurState(PLAYER_STATE::IDLE);

	pPlayer->SetAI(pAI);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);
}










