#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CEventMgr.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CCore.h"

#include "Gold.h"
#include "AI.h"


CMonster::CMonster()
	: mtInfo({})
	, m_iDir(1)
	, mpTarget(nullptr)
	, mAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 30.f));
	GetCollider()->SetOffsetPos(Vec2(56.f, 50.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_1", L"texture\\monster\\1.bmp");
	CreateHPbar();
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 93 * 1.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK", pTex, Vec2(0.f, 93 * 2.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DIE", pTex, Vec2(0.f, 93 * 4.f), Vec2(140.f, 93.f), Vec2(140.f, 0.f), 0.07f, 7);
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

	//if (mState == MONSTER_STATE::DEAD)
	//{
	//	if (GetAnimator()->GetCurAnimation()->IsFinish())
	//	{
	//		Vec2 vGoldPos = GetLocalPos() + Vec2(0.f, -50.f);

	//		Gold* pGold = new Gold();
	//		pGold->SetPos(vGoldPos);
	//		pGold->SetScale(Vec2(35.f, 35.f));
	//		pGold->SetName(L"Gold");
	//		CreateObject(pGold, GROUP_TYPE::GOLD);

	//		DeleteObject(this);
	//	}
	//	return;
	//}

	//if (mState == MONSTER_STATE::CREATE)
	//{
	//	if (GetAnimator()->GetCurAnimation()->IsFinish())
	//	{
	//		mState = MONSTER_STATE::NONE;
	//	}
	//	return;
	//}


	//if (mState == MONSTER_STATE::ATTACK)
	//{
	//	if (GetAnimator()->GetCurAnimation()->IsFinish())
	//	{
	//		mState = MONSTER_STATE::NONE;
	//	}
	//	return;
	//}


	//Vec2 vCurPos = GetPos(); // 현재 위치는 부모에있는 함수로 받아올수있다.

	//if (mpTarget == nullptr)
	//{
	//	return;
	//}
	//else if (mpTarget->IsDead())
	//{
	//	mpTarget = nullptr;
	//	return;
	//}

	//if (Vec2::Distance(mpTarget->GetLocalPos(), vCurPos) < 100.f)
	//{
	//	attack();
	//}
	//else
	//{
	//	Vec2 vDir = mpTarget->GetLocalPos() - vCurPos;
	//	vDir.Normalize();

	//	SetPos(vCurPos + vDir * 100.f * fDT);
	//	GetAnimator()->Play(L"RUN", true);
	//}
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
		float hp = GetHP() - 10.f;
		if (hp <= 0.f)
		{
			DeleteObject(this);
		}
		SetHP(hp);
		/*if (mState != MONSTER_STATE::DEAD)
		{
			mHp -= 1;
			if (mHp <= 0)
			{
				death();
			}   
		}*/
	}
}


void CMonster::death()
{
	GetAnimator()->Play(L"DIE", false);
	//mState = MONSTER_STATE::DEAD;
}



void CMonster::attack()
{
	GetAnimator()->Play(L"ATK", false);
	//mState = MONSTER_STATE::ATTACK;
}
