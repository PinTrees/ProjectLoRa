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

// Game Manager Header
#include "PlayerMgr.h"
#include "LevelUpUIMgr.h"

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

#include "MonsterFactory.h"
#include "HubUIMgr.h"
#include "SkillMgr.h"

#include "AstarMgr.h"


Scene_Start::Scene_Start()
	: mfMstrDelay(1.f)
	, mfCurDelay(0.f)
{
}

Scene_Start::~Scene_Start()
{
	// �̱��� �޸� ����
	LevelUpUIMgr::Dispose();
	PlayerMgr::Dispose();
	HubUIMgr::Dispose();
	SkillMgr::Dispose();
	AstarMgr::Dispose();
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
}

void Scene_Start::Enter()
{
	LoadTile(this, L"database\\map_1.tile");

	createPlayer();

	//���� ��ġ
	int iMonCount = 1;
	for (int i = 0; i < iMonCount; i++)
	{
		//CreateMonster();
	}

	int iEnvCount = 77;
	for (int i = 0; i < iEnvCount; i++)
	{
		createEnvi();
	}




	LevelUpUIMgr::GetI()->Init();
	HubUIMgr::GetI()->Init();
	SkillMgr::GetI()->Init();

	// �浹 ����
	//  Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GOLD);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ENV);

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





void Scene_Start::CreateMonster()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	// ���͸� ��ȯ�� �����ڸ� ��ġ ����
	float edgeDistance = 100.f;				// �����ڸ��κ����� �Ÿ�
	float xPos = rand() % (int)(vResolution.x - 2 * edgeDistance) + edgeDistance; // x ��ǥ ����: edgeDistance���� (���� �ػ� - 2 * edgeDistance)����
	float yPos = rand() % (int)(vResolution.y - 2 * edgeDistance) + edgeDistance; // y ��ǥ ����: edgeDistance���� (���� �ػ� - 2 * edgeDistance)����

	Vect2 vCreatePos;
	// �����ڸ� ��ġ ���
	// ���� �����ڸ�
	if (rand() % 2 == 0) 
		vCreatePos = Vect2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	// �¿� �����ڸ�
	else 
		vCreatePos = Vect2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
	
	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);


	Monster* pMonsterObj = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vCreatePos);
	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
}




void Scene_Start::createEnvi()
{
	int xPos = rand() % 20*TILE_SIZE_RENDER;
	int yPos = rand() % 20*TILE_SIZE_RENDER;
	int xIdx = xPos / TILE_SIZE_RENDER;
	int yIdx = yPos / TILE_SIZE_RENDER;

	AstarMgr::GetI()->SetWallNode(xIdx, yIdx);
	
	Vect2 vScale = Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER); 
	Vect2 vScaleOffset = vScale * 0.5f; 
	Vect2 vCreatePos = Vect2(xPos, yPos);

	Environment* pEnvObj = new Environment(L"101");

	pEnvObj->SetName(L"ENV"); 
	pEnvObj->SetScale(vScale); 
	pEnvObj->SetPos(vCreatePos + vScaleOffset);
	pEnvObj->GetCollider()->SetScale(vScale); 
	pEnvObj->GetCollider()->SetTrigger(false); 
	AddObject(pEnvObj, GROUP_TYPE::ENV); 
}



void Scene_Start::createPlayer()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(Vect2(0.f,0.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	AI<PLAYER_STATE>* pAI = new AI<PLAYER_STATE>;
	pAI->AddState(new PIdleState);
	pAI->AddState(new PRunState);
	pAI->AddState(new PDashState);
	pAI->AddState(new PAtkState);
	pAI->SetCurState(PLAYER_STATE::IDLE);

	pPlayer->SetAI(pAI);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);
}



