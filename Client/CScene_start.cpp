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

#include "MonsterFactory.h"


// UI Components Header
#include "CBtnUI.h"
#include "CImageUI.h"



Scene_Start::Scene_Start()
	: mfMstrDelay(1.f)
	, mfCurDelay(0.f)
	, mpSettingBtn(nullptr)
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

	mfCurDelay += DT;

	if (mfCurDelay > mfMstrDelay)
	{
		mfMstrDelay *= 0.999f;
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

	createMainUI();
	createPlayer();

	//몬스터 배치
	int iMonCount = 8;
	for (int i = 0; i < iMonCount; i++)
	{
		CreateMonster();
	}

	int iEnvCount = 500;
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





void Scene_Start::CreateMonster()
{
	Vect2 vResolution = CCore::GetI()->GetResolution();

	// 몬스터를 소환할 가장자리 위치 설정
	float edgeDistance = 100.f;				// 가장자리로부터의 거리
	float xPos = rand() % (int)(vResolution.x - 2 * edgeDistance) + edgeDistance; // x 좌표 범위: edgeDistance부터 (가로 해상도 - 2 * edgeDistance)까지
	float yPos = rand() % (int)(vResolution.y - 2 * edgeDistance) + edgeDistance; // y 좌표 범위: edgeDistance부터 (세로 해상도 - 2 * edgeDistance)까지

	Vect2 vCreatePos;
	// 가장자리 위치 계산
	// 상하 가장자리
	if (rand() % 2 == 0) 
		vCreatePos = Vect2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	// 좌우 가장자리
	else 
		vCreatePos = Vect2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
	
	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);


	Monster* pMonsterObj = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vCreatePos);
	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
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
	pAI->SetCurState(PLAYER_STATE::IDLE);

	pPlayer->SetAI(pAI);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);
}






void Scene_Start::createMainUI()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	CBtnUI* pSettingBtn = new CBtnUI;
	pSettingBtn->SetScale(Vect2(50.f, 50.f));
	pSettingBtn->SetPos(Vect2(vRes.x -  80.f, 50.f));
	pSettingBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Button_2", L"texture\\ui\\button\\2.bmp"));
	pSettingBtn->SetClickedCallBack(this, SCENE_FUNC(&Scene_Start::OpenSettingPanel));

	CImageUI* pImage = new CImageUI;
	pImage->SetPos(Vect2(0.f, -5.f));
	pImage->SetScale(pSettingBtn->GetScale() * 0.6f);
	pImage->SetTexture(CResMgr::GetI()->LoadTexture(L"Setting_Icon", L"texture\\ui\\icon\\setting.bmp"));
	pImage->SetRaycastTarget(false);
	pSettingBtn->AddChild(pImage);

	mpSettingBtn = pSettingBtn;

	AddObject(mpSettingBtn, GROUP_TYPE::UI);
}




void Scene_Start::OpenSettingPanel()
{
	GUIMgr::GetI()->ShowSettingUI();
}







