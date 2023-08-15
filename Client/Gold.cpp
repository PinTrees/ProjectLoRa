#include "pch.h"
#include "Gold.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "PlayerMgr.h"
#include "Player.h"
#include "HubUIMgr.h"

#include "CSound.h"


Gold::Gold()
	: mDeleteDelay(25.f)
	, mCurDelay(0.f)
	, mbGather(false)
	, mCurGatherDelay(0.f)
{
	SetName(L"Gold");

	mpCoinSound = CResMgr::GetI()->LoadSound(L"Sound_Coin", L"sound\\coin.wav");

	SetScale(Vect2(36.f, 36.f) * 0.6f);

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Gold_1", L"texture\\gold\\coin_1.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(128.f, 128.f), Vect2(128.f, 0.f), 0.05f, 6);
	GetAnimator()->Play(L"IDLE", true);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));
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

	if (mbGather)
	{
		Vect2 vPos = GetPos();
		Vect2 vTargetPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

		mCurGatherDelay += DT;

		float t = mCurGatherDelay / mGatherDelay;
		Vect2 lerpPos = vPos + (vTargetPos - vPos) * t;

		SetPos(lerpPos);

		if (mCurGatherDelay > mGatherDelay)
		{
			PlayerMgr::GetI()->AddGold(5);
			HubUIMgr::GetI()->BuildGoldText();

			if (mpCoinSound)
				mpCoinSound->Play();

			DeleteObject(this);
		}
	}
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

