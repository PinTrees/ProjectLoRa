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

#define HITRANGE 100.f

Stone::Stone()
	: mCurTime()
	, mArrivalTime(2.f)
	, mRemainTime()
	, mIsAtk(false)
{
	//mpSound = CResMgr::GetI()->LoadSound(L"Skill_6", L"sound\\skill\\6_2.wav");
	//mpSound->SetVolumeOffset(-300);
	SetName(L"Stone");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Grenade", L"texture\\effect\\2.bmp");
	CTexture* pTex_1 = CResMgr::GetI()->LoadTexture(L"Skill_Boss_1", L"texture\\effect\\13.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Grenade", pTex, Vect2(40.f, 0.f), Vect2(40.f, 52.f), Vect2(40.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"ATK", pTex_1, Vect2(0.f, 0.f), Vect2(111.f, 111.f), Vect2(111.f, 0.f), 0.07f, 17);
	GetAnimator()->FindAnimation(L"ATK")->SetAllFrameOffet(Vect2(0.f, -50.f));
	SetScale(Vect2(150.f, 150.f));

	GetAnimator()->Play(L"Grenade", true);
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

	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	if (mCurTime > 1)				// 지정한 시간이 지나면
	{
		mCurTime = 0;
		Vect2 r = playerPos - mvTargetPoint;
		if (r.Length() < HITRANGE)
		{
			PlayerMgr::GetI()->GetPlayer()->AddDamage(10.f);
		}
		mIsAtk = true;
		GetAnimator()->Play(L"ATK", false);
		SetScale(GetScale() * 1.35f);
		return;
	}


	mCurTime += DT / mArrivalTime;				// 베지어 곡선을 적용
	mRemainTime = 1 - mCurTime;

	Vect2 V0 = mvStartPoint * mRemainTime + mvCurvePoint * mCurTime;
	Vect2 V1 = mvCurvePoint * mRemainTime + mvTargetPoint * mCurTime;
	Vect2 V2 = V0 * mRemainTime + V1 * mCurTime;

	SetPos(V2);
}

void Stone::Render(HDC _dc)
{
	CompnentRender(_dc);

	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(_dc, PEN_TYPE::RED);

	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(mvTargetPoint);
	float pivotSize = 3.f;

	Ellipse(_dc
		, (int)(vRenderPos.x - HITRANGE * 0.5f)
		, (int)(vRenderPos.y - HITRANGE * 0.5f)
		, (int)(vRenderPos.x + HITRANGE * 0.5f)
		, (int)(vRenderPos.y + HITRANGE * 0.5f));

}

void Stone::OnCollisionEnter(CCollider* _pOther)
{
}