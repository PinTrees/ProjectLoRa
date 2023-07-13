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

<<<<<<< Updated upstream
#include "CPlayer.h"
=======
#include "Player.h"
>>>>>>> Stashed changes

Gun::Gun(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, mDelay(1.f)
	, mCurDelay(0.f)
	, mOwner(nullptr)
<<<<<<< Updated upstream
{
=======
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

>>>>>>> Stashed changes
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"GUN" + _type, L"texture\\gun\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
<<<<<<< Updated upstream
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(28.f, 16.f), Vec2(28.f, 0.f), 5.f, 1);
		SetScale(Vec2(28.f, 16.f) * 1.5f);
		SetPivot(Vec2(-30.f, 0.f));
=======
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(28.f, 16.f), Vect2(28.f, 0.f), 5.f, 1);
		SetScale(Vect2(28.f, 16.f) * 1.5f);
		SetPivot(Vect2(-30.f, 0.f));
>>>>>>> Stashed changes
		SetAngleOffset(180);


	}

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	GetAnimator()->Play(L"IDLE", true);
}




Gun::~Gun()
{

}

<<<<<<< Updated upstream
=======

void Gun::Shot()
{
	
}


>>>>>>> Stashed changes
void Gun::Update()
{
	GetAnimator()->Update();

	if (mOwner == nullptr)
	{
		return;
	}

<<<<<<< Updated upstream
	SetPos(mOwner->GetLocalPos() + Vec2(0.f, -45.f));
=======
	SetPos(mOwner->GetLocalPos() + Vect2(0.f, -45.f));
>>>>>>> Stashed changes
}

void Gun::Render(HDC _dc)
{
<<<<<<< Updated upstream
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
=======
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();
>>>>>>> Stashed changes

	CompnentRender(_dc);
}
