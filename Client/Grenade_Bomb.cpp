#include "pch.h"
#include "Grenade_Bomb.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"




Grenade_Bomb::Grenade_Bomb()
	: mCurDelay()
{
	SetMaxDelay(2.7f);		// 스킬 지속시간 세팅
	SetDamageDelay(0.9f);	// ~초마다 데미지를 입힘
	SetDamage(10.f);
	SetName(L"Grenade_Bomb");
	CreateCollider();
	GetCollider()->SetScale(Vect2(60.f, 40.f) * 3.f);
	GetCollider()->SetOffsetPos(Vect2(0.f, 20.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Grenade_Bomb", L"texture\\effect\\3.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Grenade_Bomb", pTex, Vect2(0.f, 0.f), Vect2(60.f, 80.f), Vect2(60.f, 0.f), 0.07f, 10);
	SetScale(Vect2(60.f, 80.f) * 4.f);

	GetAnimator()->Play(L"Grenade_Bomb", true);
}

Grenade_Bomb::~Grenade_Bomb()
{
}

void Grenade_Bomb::Update()
{
	if (mCurDelay > GetMaxDelay())
	{
		DeleteObject(this);
		return;
	}

	GetAnimator()->Update();
	mCurDelay += DT;
}

void Grenade_Bomb::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
