#include "pch.h"
#include "Gun.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "Particle.h"

#include "Player.h"

Gun::Gun(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, mDelay(1.f)
	, mCurDelay(0.f)
	, mOwner(nullptr)
	, mInfo({})
{
	// 파일 처리
	mInfo.mAtkDamage = 10.f;
	mInfo.mAtkRange = 1000.f;
	mInfo.mAtkSpeed = 300.f;
	mInfo.mPenetration = 3;
	mInfo.mReloadSpeed = 0.3f;
	mInfo.mShotAngle = 30.f;
	mInfo.mShotSpeed = 0.3f;

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"GUN" + _type, L"texture\\gun\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
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
	
}


void Gun::Update()
{
	GetAnimator()->Update();

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
