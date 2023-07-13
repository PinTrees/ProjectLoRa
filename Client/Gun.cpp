#include "pch.h"
#include "Gun.h"

#include "CScene.h"

// Core Manager Header
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

// Utility Header
#include "Random.h"

#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

// GameObject Header
#include "Particle.h"
#include "Bullet.h"
#include "Player.h"


Gun::Gun(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, mDelay(1.f)
	, mCurDelay(0.f)
	, mOwner(nullptr)
	, mInfo({})
	, mbReload(false)
{
	// 파일 처리
	mInfo.atkDamage = 10.f;
	mInfo.atkRange = 1000.f;
	mInfo.atkSpeed = 300.f;
	mInfo.penetration = 3;
	
	mInfo.reloadSpeed = 0.1f;
	mInfo.shotDelay = 0.1f;

	mInfo.shotAngle = 30.f;
	mInfo.shotCount = 10;
	mInfo.shotSpeed = 0.3f;
	mInfo.texture = L"1";
	mInfo.bulletType = L"3";

	mInfo.bulletCount = 10;
	mInfo.curBulletCount = mInfo.bulletCount;
	mInfo.splitCount = 3;
	mInfo.bouncCount = 1;

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"GUN" + mInfo.texture, L"texture\\gun\\" + mInfo.texture + L".bmp");
	CreateAnimator();

	if (mInfo.texture == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(28.f, 16.f), Vect2(28.f, 0.f), 5.f, 1);
		SetScale(Vect2(28.f, 16.f) * 1.5f);
		SetPivot(Vect2(-30.f, 0.f));
		SetAngleOffset(180);
	}

	GetAnimator()->Play(L"IDLE", true);
}

Gun::~Gun()
{
}


void Gun::Shot()
{
	if (mbReload)
		return;

	if (mInfo.curBulletCount <= 0)
	{
		Reload();
		return;
	}


	--mInfo.curBulletCount;
	Vect2 vShotPos = GetPos();

	// 일정 발사각 범위 내의 랜덤한 방향을 생성합니다.
	int shotAngle = (int)(mInfo.shotAngle * 0.5f);
	float angle = GetAngleOrg() + (float)CRandom::GetI()->Next(shotAngle * -1, shotAngle); // 랜덤한 각도
	Vect2 vDir = Vect2::FromAngle(angle);


	// 총알 오브젝트
	tBullet bInfo = {};
	bInfo.damage = mInfo.atkDamage;
	bInfo.bounceCount = (float)mInfo.bouncCount;
	bInfo.penetrationCount = (float)mInfo.penetration;
	bInfo.splitCount = (float)mInfo.splitCount;

	Bullet* pBullet = new Bullet(mInfo.bulletType);
	pBullet->SetPos(vShotPos + vDir.Normalize() * 35.f);
	pBullet->SetDir(vDir);
	pBullet->SetInfo(bInfo);
	pBullet->SetName(L"Missile_Player");
	    
	CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);
}


void Gun::Reload()
{
	mbReload = true;
	mCurDelay = 0.f;
}


void Gun::Update()
{
	GetAnimator()->Update();

	if (mbReload)
	{
		mCurDelay += DT;
		if (mCurDelay >= mInfo.reloadSpeed)
		{
			mInfo.curBulletCount = mInfo.bulletCount;
			mbReload = false;
		}
	}

	if (mOwner == nullptr)
	{
		return;
	}

	SetPos(mOwner->GetLocalPos() + Vect2(0.f, -45.f));
}

void Gun::Render(HDC _dc)
{
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	CompnentRender(_dc);
}
