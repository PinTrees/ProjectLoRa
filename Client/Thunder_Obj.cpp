#include "pch.h"
#include "Thunder_Obj.h"

#include "CObject.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "Random.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "ThunderBoom.h"
#include "Particle.h"




Thunder_Obj::Thunder_Obj()
	: mCurDelay()
	, mbEffect(false)
{
	SetMaxDelay(0.5f);		// 스킬 지속시간 세팅
	SetDamageDelay(0.9f);	// ~초마다 데미지를 입힘

	SetName(L"Thunder");
	SetScale(Vect2(48.f, 400.f) * 2.f);

	CreateCollider();
	GetCollider()->SetScale(Vect2(100.f, 100.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, -50.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Thunder", L"texture\\effect\\102.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Thunder_1", pTex, Vect2(0.f, 0.f), Vect2(48.f, 128.f), Vect2(48.f, 0.f), 0.05f, 7);
	GetAnimator()->CreateAnimation(L"Thunder_2", pTex, Vect2(48.f, 0.f) * 6, Vect2(48.f, 128.f), Vect2(48.f, 0.f), 0.05f, 6);
	GetAnimator()->FindAnimation(L"Thunder_1")->SetAllFrameOffet(Vect2(0.f, GetScale().y * -0.5f));
	GetAnimator()->FindAnimation(L"Thunder_2")->SetAllFrameOffet(Vect2(0.f, GetScale().y * -0.5f));

	if (CRandom::GetI()->Next(0, 2) == 1)
	{
		GetAnimator()->Play(L"Thunder_1", false);
	}
	else
	{
		GetAnimator()->Play(L"Thunder_2", false);
	}
}

Thunder_Obj::~Thunder_Obj()
{
}

void Thunder_Obj::Update()
{
	mCurDelay += DT;

	if (mCurDelay >= GetMaxDelay())		// 스킬 지속시간이 지나면 오브젝트를 삭제
	{
		DeleteObject(this);
		mCurDelay = 0.f;
		return;
	}

	if (mCurDelay >= 0.15f && !mbEffect)
	{
		mbEffect = true;

		ThunderBoom* bomb = new ThunderBoom;	// 폭발오브젝트를 생성한다.
		bomb->SetPos(GetPos());
		bomb->SetOwner(GetOwner());
		CreateObject(bomb, GROUP_TYPE::PROJ_PLAYER);
	}

	GetAnimator()->Update();
}

void Thunder_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}


void Thunder_Obj::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetName() == L"Monster")
	{
		Particle* pParticle = new Particle(L"105");
		pParticle->SetPos(pObj->GetLocalPos());
		pParticle->SetScale(pParticle->GetScale() * 0.75f);
		CreateObject(pParticle, GROUP_TYPE::EFFECT);
	}
}
