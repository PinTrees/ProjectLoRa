#include "pch.h"
#include "Monster.h"

#include "CCore.h"

// Include Manager
#include "CTimeMgr.h"
#include "CResMgr.h"

// System Module Header
#include "Random.h"

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

#include "CombatText.h"



Monster::Monster(const wstring& uid)
	: mtInfo({})
	, mAI(nullptr)
{
	mtInfo.UID = uid;

	CreateCollider();

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_" + uid, L"texture\\monster\\" + uid + L".bmp");
	CreateAnimator();
	
	if (mtInfo.UID == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
		GetAnimator()->CreateAnimation(L"RUN", pTex, Vect2(0.f, 93 * 1.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
		GetAnimator()->CreateAnimation(L"ATK", pTex, Vect2(0.f, 93 * 2.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
		GetAnimator()->CreateAnimation(L"DEAD", pTex, Vect2(0.f, 93 * 4.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 7);
		GetAnimator()->CreateAnimation(L"CREATE", pTex, Vect2(0.f, 93 * 8.f), Vect2(140.f, 93.f), Vect2(140.f, 0.f), 0.07f, 8);
		GetCollider()->SetScale(Vect2(40.f, 40.f));
		GetCollider()->SetOffsetPos(Vect2(75.f, 35.f));
		SetScale(Vect2(280.f, 180.f) * 0.8f);
		SetPivot(Vect2(75.f, 35.f));
	}
	else if (mtInfo.UID == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 48.f * 1.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"RUN", pTex, Vect2(0.f, 48.f * 3.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"ATK", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"DEAD", pTex, Vect2(0.f, 48.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		//GetAnimator()->CreateAnimation(L"CREATE", pTex, Vect2(0.f, 48.f * 8.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.07f, 4);
		GetCollider()->SetOffsetPos(Vect2::zero);
		SetScale(Vect2(48.f, 48.f) * 1.3f);
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));
	}

	GetCollider()->SetScale(GetScale() * 0.6f);
	GetCollider()->SetOffsetPos(GetPivot() * 0.4f);

	GetAnimator()->Play(L"IDLE", true);

	mHpBar = new BarUI;
	mHpBar->SetPivot(Vect2(0.f, GetScale().y * -0.4f));
	mHpBar->SetScale(Vect2(45.f, 5.f));
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
		mHpBar->SetFillAmount((float)mtInfo.curHp / (float)mtInfo.hp);
		mHpBar->SetPos(GetPos());
	}
}

void Monster::SetAI(AI<MONSTER_STATE>* pAI)
{
	mAI = pAI;
	mAI->SetOwner(this);
}

void Monster::AddDamage(float damage)
{
	mtInfo.curHp -= damage;
	if (mtInfo.curHp < 0) mtInfo.curHp = 0;


	Vect2 vOff = Vect2((float)CRandom::GetI()->Next(-20, 20), (float)CRandom::GetI()->Next(-20, 20));

	CombatText* pCbTex = new CombatText;
	pCbTex->SetPos(GetLocalPos());
	pCbTex->SetText(std::to_wstring((int)damage));
	CreateObject(pCbTex, GROUP_TYPE::UI);
}


void Monster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
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

