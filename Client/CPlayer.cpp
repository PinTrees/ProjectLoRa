#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneMgr.h"


#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	:mPTex(nullptr)
{
	// Texture 로딩하기
	mPTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;

	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;

	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;

	}

	if (KEY_TAP(KEY::SPACE))
	{
		createMissile();
	}

	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	int iWidth = (int)mPTex->Width();
	int iHeigth = (int)mPTex->Heigth();

	Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeigth / 2))
	//	, iWidth, iHeigth, mPTex->GetDC(), 0, 0, SRCCOPY);

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeigth / 2))
		, iWidth, iHeigth
		, mPTex->GetDC()
		, 0, 0, iWidth, iHeigth
		, RGB(255, 0, 255));

	//컴포넌트 ( 충돌체 , ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}

void CPlayer::createMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}


