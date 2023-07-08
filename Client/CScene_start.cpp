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

#include "MonsterFactory.h"
#include "PlayerMgr.h"

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

void Scene_Start::Enter()
{
	LoadTile(this, L"database\\map_1.tile");

	Player* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(Vec2(640.f, 384.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	PlayerMgr::GetI()->SetPlayer(pPlayer);
	CCamera::GetI()->SetTarget(pPlayer);

	//���� ��ġ
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


	// �浹 ����
	//  Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GOLD);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::ENV);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ENV);

	// Camera Look ����
	Vec2 vResolution = CCore::GetI()->GetResolution();
	CCamera::GetI()->SetLookAt(vResolution / 2.f);
	CCamera::GetI()->FadeOut(2.f);
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
	Vec2 vResolution = CCore::GetI()->GetResolution();

	// ���͸� ��ȯ�� �����ڸ� ��ġ ����
	float edgeDistance = 100.f;				// �����ڸ��κ����� �Ÿ�
	float xPos = rand() % (int)(vResolution.x - 2 * edgeDistance) + edgeDistance; // x ��ǥ ����: edgeDistance���� (���� �ػ� - 2 * edgeDistance)����
	float yPos = rand() % (int)(vResolution.y - 2 * edgeDistance) + edgeDistance; // y ��ǥ ����: edgeDistance���� (���� �ػ� - 2 * edgeDistance)����

	Vec2 vCreatePos;
	// �����ڸ� ��ġ ���
	// ���� �����ڸ�
	if (rand() % 2 == 0) 
		vCreatePos = Vec2(xPos, rand() % 2 == 0 ? edgeDistance : vResolution.y - edgeDistance);
	// �¿� �����ڸ�
	else 
		vCreatePos = Vec2(rand() % 2 == 0 ? edgeDistance : vResolution.x - edgeDistance, yPos);
	
	vCreatePos = CCamera::GetI()->GetRealPos(vCreatePos);


	CMonster* pMonsterObj = MonsterFactory::CreateMonster(MONSTER_TYPE::NORMAL, vCreatePos);
	pMonsterObj->SetName(L"Monster");
	pMonsterObj->SetScale(Vec2(280.f, 180.f));
	pMonsterObj->GetCollider()->SetTrigger(false);

	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
}




void Scene_Start::createEnvi()
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



