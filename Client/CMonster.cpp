#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CScene.h"

#include "CCore.h"

#include "Gold.h"
#include "AI.h"


CMonster::CMonster()
	: mtInfo({})
	, mAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 60.f));
	GetCollider()->SetOffsetPos(Vec2(75.f, 50.f));
	SetPivot(Vec2(75.f, 35.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_1", L"texture\\monster\\1.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 93 * 1.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK", pTex, Vec2(0.f, 93 * 2.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DEAD", pTex, Vec2(0.f, 93 * 4.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 7);
	GetAnimator()->CreateAnimation(L"CREATE", pTex, Vec2(0.f, 93 * 8.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);

	GetAnimator()->Play(L"IDLE", true);
}

CMonster::~CMonster()
{
	if (nullptr != mAI)
		delete mAI;
}


void CMonster::Render(HDC _dc)
{
	CompnentRender(_dc);
}


void CMonster::Update()
{
	GetAnimator()->Update();

	if (nullptr != mAI)
		mAI->Update();
}

void CMonster::SetAI(AI* pAI)
{
	mAI = pAI;
	mAI->mOwner = this;
}


void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		mtInfo.curHp -= 5;

		tForce fc = {};
		fc.radius = 75.f;
		fc.force = 200.f;
		fc.speed = 3.f;
		fc.pos = pOtherObj->GetLocalPos() - (GetLocalPos() - pOtherObj->GetLocalPos()).Normalize() * 5.f;

		CreateForce(fc);
	}
}

