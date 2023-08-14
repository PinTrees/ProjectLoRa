#include "pch.h"
#include "IceBolt_Effect.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "Monster.h"


IceBolt_Effect::IceBolt_Effect()
	: mCurTime()
	, mFreezeTime(3.f)
	, mDeFrostTime(0.5f)
	, mFreeze(false)
	, mvecIcedMon{}
{
	SetMaxDelay(2.7f);			// 스킬 지속시간 세팅
	SetName(L"IceBolt_Effect"); // 

	SetAlpha(180);
	SetScale(Vect2(48.f, 64.f) * 1.5f);

	CreateAnimator();

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"IceBolt_Effect", L"texture\\effect\\9.bmp");
	GetAnimator()->CreateAnimation(L"IceBolt_Effect_Freeze", pTex, Vect2(0.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.07f, 10);
	GetAnimator()->CreateAnimation(L"IceBolt_Effect_Freezing", pTex, Vect2(432.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.6f, 1);
	GetAnimator()->CreateAnimation(L"IceBolt_Effect_DeFrost", pTex, Vect2(480.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.07f, 6);
	
	GetAnimator()->Play(L"IceBolt_Effect_Freeze", false);
}

IceBolt_Effect::~IceBolt_Effect()
{
}

void IceBolt_Effect::Update()
{
	mCurTime += DT;
	GetAnimator()->Update();

	if (mvecIcedMon)
	{
		if ((Monster*)mvecIcedMon->IsDead())
		{
			mvecIcedMon = nullptr;

			GetAnimator()->Play(L"IceBolt_Effect_DeFrost", false);
			mCurTime = 0.f;
			mFreeze = true;
		}
	}
	

	if (!mFreeze && mCurTime >= mFreezeTime)
	{
		GetAnimator()->Play(L"IceBolt_Effect_DeFrost", false);
		mCurTime = 0.f;
		mFreeze = true;
	}

	if (mFreeze && mCurTime >= mDeFrostTime)
	{
		DeleteObject(this);
	}

	if (!mFreeze && GetAnimator()->GetCurAnimation()->IsFinish())
	{
		GetAnimator()->Play(L"IceBolt_Effect_Freezing", true);
	}
}

void IceBolt_Effect::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}