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
	SetName(L"Grenade_Bomb");
	CreateCollider();
	GetCollider()->SetScale(Vect2(180.f, 150.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 80.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Grenade_Bomb", L"texture\\effect\\8.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Grenade_Bomb", pTex, Vect2(0.f, 0.f), Vect2(32.f, 32.f), Vect2(32.f, 0.f), 0.1f, 9);
	SetScale(Vect2(300.f, 300.f));

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
