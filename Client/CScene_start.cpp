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


#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"


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


	//  Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);
	// CObject* pOtherPlayer = pObj->Clone();
	// pOtherPlayer->SetPos(Vec2(640.f, 314.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// CCamera::GetI()->SetTarget(pObj);


	//���� ��ġ
	Vec2 vResolution = CCore::GetI()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL,vResolution / 2.f -Vec2(0.f,300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// CreateObject(pMon, GROUP_TYPE::MONSTER);

	// Ÿ�Ϸε�
	// Loadtile



	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);



	// Camera Look ����
	CCamera::GetI()->SetLookAt(vResolution / 2.f);



	// ī�޷� ȿ�� ����

	CCamera::GetI()->FadeOut(1.f);
	CCamera::GetI()->FadeIn(1.f);
}


//������� ������ ����Ǵ� �Լ�
void CScene_start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetI()->Reset();

}


