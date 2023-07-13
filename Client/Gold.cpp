#include "pch.h"
#include "Gold.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"

Gold::Gold()
	: mDeleteDelay(25.f)
	, mCurDelay(0.f)
{
	CreateCollider();
<<<<<<< Updated upstream
	GetCollider()->SetScale(Vec2(55.f, 55.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Gold_1", L"texture\\gold\\gold_1.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(128.f, 128.f), 0.1f, 1);
	GetAnimator()->Play(L"IDLE", true);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, 0.f));
=======
	GetCollider()->SetScale(Vect2(55.f, 55.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Gold_1", L"texture\\gold\\coin_1.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(128.f, 128.f), Vect2(128.f, 0.f), 0.05f, 6);
	GetAnimator()->Play(L"IDLE", true);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));
>>>>>>> Stashed changes
}


Gold::~Gold()
{
}


void Gold::Update()
{
	mCurDelay += DT;
	if (mCurDelay > mDeleteDelay)
	{
		DeleteObject(this);
		mCurDelay = 0.f;
		return;
	}

	GetAnimator()->Update();
}


void Gold::Render(HDC _dc)
{
	CompnentRender(_dc);
}


void Gold::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}

