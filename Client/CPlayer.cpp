#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneMgr.h"


#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CMissile.h"

#include "CPathMgr.h"
#include "CTexture.h"

CPlayer::CPlayer()
	:mPTex(nullptr)
{
	// Texture 로딩하기
	mPTex = new CTexture();

	wstring strFilepath = CPathMgr::GetI()->GetContentPath();
	strFilepath += L"texture\\Player.bmp";
	mPTex->Load(strFilepath);


}

CPlayer::~CPlayer()
{
	if (nullptr != mPTex)
		delete mPTex;
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

	if (KEY_HOLD(KEY::SPACE))
	{
		CreateMissile();
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
}

void CPlayer::CreateMissile()
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


