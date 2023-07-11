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

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"



CScene_start::CScene_start()
	:mbUseForce(false)
	, mfForceRadius(500.f)
	, mfCurRadius(0.f)
	, mfForce(500.f)
{
}

CScene_start::~CScene_start()
{
}

void CScene_start::Update()
{
	if (KEY_HOLD(KEY::RBTN))
	{
		mbUseForce = true;
		CreateForce();
	}
	else
	{
		mbUseForce = false;
	}




	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (mbUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - mvForcePos;
					float fLen = vDiff.Length();
					if (fLen < mfForceRadius)
					{

						float fRatio = 1.f - (fLen / mfForceRadius);
						float fForce = mfForce * fRatio;
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}
				vecObj[j]->Update();
			}
		}
	}









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

void CScene_start::Render(HDC _dc)
{
	CScene::Render(_dc);

	if (!mbUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	mfCurRadius += mfForceRadius * 3.f * fDT;

	if (mfCurRadius > mfForceRadius)
	{
		mfCurRadius = 0.f;
	}
	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(mvForcePos);

	Ellipse(_dc
		, vRenderPos.x - mfCurRadius
		, vRenderPos.y - mfCurRadius
		, vRenderPos.x + mfCurRadius
		, vRenderPos.y + mfCurRadius);



}

void CScene_start::Enter()
{


	//  Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);
	// CObject* pOtherPlayer = pObj->Clone();
	// pOtherPlayer->SetPos(Vec2(640.f, 314.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// CCamera::GetI()->SetTarget(pObj);


	//몬스터 배치
	Vec2 vResolution = CCore::GetI()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// CreateObject(pMon, GROUP_TYPE::MONSTER);

	// 타일로딩
	// Loadtile



	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetI()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);



	// Camera Look 지정
	CCamera::GetI()->SetLookAt(vResolution / 2.f);



	// 카메로 효과 지정

	CCamera::GetI()->FadeOut(1.f);
	CCamera::GetI()->FadeIn(1.f);
}


//현재씬을 나갈때 실행되는 함수
void CScene_start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetI()->Reset();

}


void CScene_start::CreateForce()
{
	mvForcePos = CCamera::GetI()->GetRealPos(MOUSE_POS);
}