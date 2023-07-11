#include "pch.h"
#include "Monster.h"

#include "CCore.h"

// Include Manager
#include "CTimeMgr.h"
#include "CResMgr.h"

// Include Componets
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CScene.h"
#include "AI.h"
#include "Gold.h"

// Include UI
#include "BarUI.h"



Monster::Monster()
	: mtInfo({})
	, mAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vect2(40.f, 40.f));
	GetCollider()->SetOffsetPos(Vect2(75.f, 35.f));
	SetPivot(Vect2(75.f, 35.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_1", L"texture\\monster\\1.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN", pTex, Vect2(0.f, 93 * 1.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK", pTex, Vect2(0.f, 93 * 2.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DEAD", pTex, Vect2(0.f, 93 * 4.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 7);
	GetAnimator()->CreateAnimation(L"CREATE", pTex, Vect2(0.f, 93 * 8.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);

	GetAnimator()->Play(L"IDLE", true);

	mHpBar = new BarUI;
	mHpBar->SetPivot(Vect2(70.f, -25.f));
	mHpBar->SetScale(Vect2(50.f, 4.f));
	mHpBar->SetColor(RGB(255, 0, 0));
	CreateObject(mHpBar, GROUP_TYPE::UI);
}

Monster::~Monster()
{
	if (nullptr != mAI)
		delete mAI;
}


void Monster::Render(HDC _dc)
{
	CompnentRender(_dc);
}


void Monster::Update()
{
	GetAnimator()->Update();

	if (nullptr != mAI)
		mAI->Update();

	if (nullptr != mHpBar)
	{
		mHpBar->SetAmount((float)mtInfo.curHp / (float)mtInfo.hp);
		mHpBar->SetPos(GetPos());
	}
}

void Monster::SetAI(AI* pAI)
{
	mAI = pAI;
	mAI->SetOwner(this);
}


void Monster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		mtInfo.curHp -= 5;
		if (mtInfo.curHp < 0) mtInfo.curHp = 0;

		tForce fc = {};
		fc.radius = 60.f;
		fc.force = 150.f;
		fc.speed = 2.5f;
		fc.pos = pOtherObj->GetLocalPos() - (GetLocalPos() - pOtherObj->GetLocalPos()).Normalize() * 3.f;

		CreateForce(fc);
	}
}


void Monster::OnDestroy()
{
	DeleteObject(mHpBar);
}

