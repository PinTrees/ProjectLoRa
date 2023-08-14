#include "pch.h"
#include "Stone.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "PlayerMgr.h"
#include "CSceneMgr.h"
#include "Random.h"

#include "CScene.h"
#include "Player.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "SelectGDI.h"

#include "CAnimation.h"
#include "CTexture.h"

#define HITRANGE 100.f

Stone::Stone()
	: mCurTime()
	, mArrivalTime(2.f)
	, mRemainTime()
	, mIsAtk(false)
{
	//mpSound->SetVolumeOffset(-300);
	SetName(L"Stone");

	mFloorTex = CResMgr::GetI()->LoadTexture(L"Boss_Skill_G", L"texture\\monster\\rang.bmp");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Grenade", L"texture\\effect\\2.bmp");
	CTexture* pTex_1 = CResMgr::GetI()->LoadTexture(L"Skill_Boss_1", L"texture\\effect\\13.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Grenade", pTex, Vect2(40.f, 0.f), Vect2(40.f, 52.f), Vect2(40.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"ATK", pTex_1, Vect2(0.f, 0.f), Vect2(111.f, 111.f), Vect2(111.f, 0.f), 0.07f, 17);
	GetAnimator()->FindAnimation(L"ATK")->SetAllFrameOffet(Vect2(0.f, -50.f));
	SetScale(Vect2(150.f, 150.f));

	//GetAnimator()->Play(L"Grenade", true);
}

Stone::~Stone()
{
}


void Stone::Update()
{
	GetAnimator()->Update();

	if (mIsAtk)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			DeleteObject(this);
		}
		return;
	}


	if (mCurTime > 1)				// 지정한 시간이 지나면
	{
		//Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

		mCurTime = 0;
		GetAnimator()->Play(L"ATK", false);
		mIsAtk = true;
		/*Vect2 r = playerPos - mvTargetPoint;
		if (r.Length() < HITRANGE)
		{
			PlayerMgr::GetI()->GetPlayer()->AddDamage(10.f);
		}
		
		SetScale(GetScale() * 1.35f);*/
		SetScale(GetScale() * 1.35f);
		
		return;
	}

	SetPos(mvTargetPoint);
	mCurTime += DT / mArrivalTime;				// 베지어 곡선을 적용
	//mRemainTime = 1 - mCurTime;

	//Vect2 V0 = mvStartPoint * mRemainTime + mvCurvePoint * mCurTime;
	//Vect2 V1 = mvCurvePoint * mRemainTime + mvTargetPoint * mCurTime;
	//Vect2 V2 = V0 * mRemainTime + V1 * mCurTime;

}

void Stone::Render(HDC dc)
{
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mvTargetPoint);
	Vect2 vScale = Vect2(100.f, 100.f) * 1.5f;
	Vect2 vOffset = Vect2(0.f, 25.f);
	float pivotSize = 3.f;

	if (mFloorTex)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = mIsAtk ? 0 : 68;

		AlphaBlend(dc
			, (int)(vRenderPos.x + vOffset.x - vScale.x * 0.5f)
			, (int)(vRenderPos.y + vOffset.y - vScale.y * 0.5f)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, mFloorTex->GetDC()
			, 0, 0
			, (int)mFloorTex->Width()
			, (int)mFloorTex->Heigth()
			, bf);
	}

	CompnentRender(dc);
}

void Stone::OnCollisionEnter(CCollider* _pOther)
{
}