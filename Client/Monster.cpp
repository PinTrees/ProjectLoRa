#include "pch.h"
#include "Monster.h"

#include "CCore.h"

// Include Manager
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "PlayerMgr.h"

// System Module Header
#include "Random.h"

// Include Componets
#include "CCollider.h"
#include "RigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CScene.h"
#include "AI.h"
#include "Gold.h"
#include "CSound.h"

// Include UI
#include "BarUI.h"

#include "CombatText.h"
#include "SelectGDI.h"

#include "Player.h"
#include "SettingMgr.h"


Monster::Monster(MONSTER_TYPE Type, const wstring& uid)
	: mtInfo({})
	, mAI(nullptr)
	, mType(Type)
	, mCurDamageDelay()
	, mHitSound(nullptr)
	, mvShadowOffset(Vect2::zero)
	, mvShadowScale(Vect2::zero)
{
	// Load ------------------------
	mHitSound = CResMgr::GetI()->LoadSound(L"Sound_Hit", L"sound\\atk.wav");
	mHitSound->SetVolumeOffset(-1300);
	mpShadowTex = CResMgr::GetI()->LoadTexture(L"Shadow_2", L"texture\\shadow\\2.bmp");

	mtInfo.UID = uid;

	SetName(L"Monster");

	CreateCollider();
	CreateAnimator();
	CreateRigidBody();
	GetRigidBody()->SetMess(1.f);
	GetRigidBody()->SetMaxVelocity(Vect2(50.f, 50.f));

	mHpBar = new BarUI;
	mHpBar->SetScale(Vect2(40.f, 4.f));
	mHpBar->SetColor(RGB(255, 0, 0));
	CreateObject(mHpBar, GROUP_TYPE::UI);

	if (mtInfo.UID == L"3")
	{
		float scale = 0.95f;
		mvShadowScale = Vect2(50.f, 25.f) * scale;
		mvShadowOffset = Vect2(0.f, 70.f) * scale;

		CTexture* pTex_r = CResMgr::GetI()->LoadTexture(L"Monster_3_r", L"texture\\monster\\3_r.bmp");
		CTexture* pTex_l = CResMgr::GetI()->LoadTexture(L"Monster_3_l", L"texture\\monster\\3_l.bmp");

		Vect2 vSliseSize = Vect2(128.f, 128.f);
		Vect2 vStepSize = Vect2(128.f, 0.f);
		Vect2 vLtPos = Vect2(0.f, 128.f);
		Vect2 vRtPos = Vect2(2560.f, 128.f);

		GetAnimator()->CreateAnimation(L"IDLE", pTex_r, vLtPos * 0.f, vSliseSize, vStepSize, 0.07f, 8);
		GetAnimator()->CreateAnimation(L"RUN_R", pTex_r, vLtPos * 1.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"ATK_R", pTex_r, vLtPos * 3.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"DEAD_R", pTex_r, vLtPos * 9.f, vSliseSize, vStepSize, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"HIT_R", pTex_r, vLtPos * 8.f, vSliseSize, vStepSize, 0.07f, 2);
		
		GetAnimator()->CreateAnimation(L"RUN_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 1.f), vSliseSize, vStepSize * -1.f, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"DEAD_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 9.f), vSliseSize, vStepSize * -1.f, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"HIT_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 8.f), vSliseSize, vStepSize * -1.f, 0.07f, 2);
		GetAnimator()->CreateAnimation(L"ATK_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 3.f), vSliseSize, vStepSize * -1.f, 0.07f, 7);

		SetScale(Vect2(128.f, 128.f) * scale);
		GetCollider()->SetScale(Vect2(30.f, 35.f));
		GetCollider()->SetOffsetPos(Vect2(0.f, 25.f));
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));
		
		mHpBar->SetPivot(Vect2(0.f, -12.f));
	}
	else if (mtInfo.UID == L"4")
	{
		float scale = 1.f;
		mvShadowScale = Vect2(50.f, 25.f) * scale;
		mvShadowOffset = Vect2(0.f, 70.f) * scale;

		CTexture* pTex_r = CResMgr::GetI()->LoadTexture(L"Monster_4_r", L"texture\\monster\\4.bmp");
		CTexture* pTex_l = CResMgr::GetI()->LoadTexture(L"Monster_4_l", L"texture\\monster\\4_l.bmp");

		Vect2 vSliseSize = Vect2(128.f, 128.f);
		Vect2 vStepSize = Vect2(128.f, 0.f);
		Vect2 vLtPos = Vect2(0.f, 128.f);
		Vect2 vRtPos = Vect2(1280.f, 128.f);

		GetAnimator()->CreateAnimation(L"IDLE", pTex_r, vLtPos * 0.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"RUN_R", pTex_r, vLtPos * 1.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"ATK_R", pTex_r, vLtPos * 6.f, vSliseSize, vStepSize, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"DEAD_R", pTex_r, vLtPos * 9.f, vSliseSize, vStepSize, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"HIT_R", pTex_r, vLtPos * 8.f, vSliseSize, vStepSize, 0.07f, 2);

		GetAnimator()->CreateAnimation(L"RUN_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 1.f), vSliseSize, vStepSize * -1.f, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"DEAD_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 9.f), vSliseSize, vStepSize * -1.f, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"HIT_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 8.f), vSliseSize, vStepSize * -1.f, 0.07f, 2);
		GetAnimator()->CreateAnimation(L"ATK_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 3.f), vSliseSize, vStepSize * -1.f, 0.07f, 7);

		SetScale(Vect2(128.f, 128.f) * scale);
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));
		GetCollider()->SetScale(Vect2(20.f, 35.f) * 1.3f);
		GetCollider()->SetOffsetPos(Vect2(0.f, 25.f));

		mHpBar->SetPivot(Vect2(0.f, -15.f));
	}
	else if (mtInfo.UID == L"5")
	{
		float scale = 1.f;
		mvShadowScale = Vect2(50.f, 25.f) * scale;
		mvShadowOffset = Vect2(0.f, 70.f) * scale;

		CTexture* pTex_r = CResMgr::GetI()->LoadTexture(L"Monster_5_r", L"texture\\monster\\5_r.bmp");
		CTexture* pTex_l = CResMgr::GetI()->LoadTexture(L"Monster_5_l", L"texture\\monster\\5_l.bmp");

		Vect2 vSliseSize = Vect2(128.f, 128.f);
		Vect2 vStepSize = Vect2(128.f, 0.f);
		Vect2 vLtPos = Vect2(0.f, 128.f);
		Vect2 vRtPos = Vect2(1280.f, 128.f);

		GetAnimator()->CreateAnimation(L"IDLE", pTex_r, vLtPos * 0.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"RUN_R", pTex_r, vLtPos * 4.f, vSliseSize, vStepSize, 0.07f, 10);
		GetAnimator()->CreateAnimation(L"ATK_R", pTex_r, vLtPos * 6.f, vSliseSize, vStepSize, 0.07f, 3);
		GetAnimator()->CreateAnimation(L"DEAD_R", pTex_r, vLtPos * 9.f, vSliseSize, vStepSize, 0.07f, 4);
		GetAnimator()->CreateAnimation(L"HIT_R", pTex_r, vLtPos * 8.f, vSliseSize, vStepSize, 0.07f, 3);

		GetAnimator()->CreateAnimation(L"RUN_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 4.f), vSliseSize, vStepSize * -1.f, 0.07f, 10);
		GetAnimator()->CreateAnimation(L"DEAD_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 9.f), vSliseSize, vStepSize * -1.f, 0.07f, 3);
		GetAnimator()->CreateAnimation(L"HIT_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 8.f), vSliseSize, vStepSize * -1.f, 0.07f, 3);
		GetAnimator()->CreateAnimation(L"ATK_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 3.f), vSliseSize, vStepSize * -1.f, 0.07f, 7);

		GetRigidBody()->IsKinematic();
		GetRigidBody()->SetMess(1.5f);
		GetRigidBody()->SetMaxVelocity(Vect2(10.f, 10.f));
		
		SetScale(Vect2(128.f, 128.f) * scale);
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));
		GetCollider()->SetScale(Vect2(30.f, 30.f) * 1.3f);
		GetCollider()->SetOffsetPos(Vect2(0.f, 50.f));

		mHpBar->SetPivot(Vect2(0.f, -15.f));
	}

	GetAnimator()->Play(L"IDLE", true);
}

Monster::~Monster()
{
	if (nullptr != mAI)
		delete mAI;

	mHitSound = nullptr;
}


void Monster::Render(HDC dc)
{
	Vect2 vPos = CCamera::GetI()->GetRenderPos(GetPos());

	if (mpShadowTex)
	{
		TransparentBlt(dc
			, (int)(vPos.x + mvShadowOffset.x - mvShadowScale.x * 0.5f)
			, (int)(vPos.y + mvShadowOffset.y - mvShadowScale.y * 0.5f)
			, (int)(mvShadowScale.x)
			, (int)(mvShadowScale.y)
			, mpShadowTex->GetDC()
			, 0, 0
			, (int)mpShadowTex->Width()
			, (int)mpShadowTex->Heigth()
			, RGB(255, 0, 255));
	}

	CompnentRender(dc);

	if (DEBUG)
	{
		if (mVecPathPos.empty())
			return;

		SelectGDI p = SelectGDI(dc, PEN_TYPE::BLUE);

		Vect2 vStartPos = CCamera::GetI()->GetRenderPos(mVecPathPos[0]);

		MoveToEx(dc, vStartPos.x, vStartPos.y, nullptr);	// 현재 좌표 설정
		for (size_t i = 1; i < mVecPathPos.size(); ++i)		// 나머지 좌표들을 순회하며 라인을 그립니다.
		{
			Vect2 vDrawPos = CCamera::GetI()->GetRenderPos(mVecPathPos[i]);
			LineTo(dc, vDrawPos.x, vDrawPos.y);
		}
	}
}


void Monster::Update()
{
	mCurDamageDelay += DT;
	mtInfo.curSpeed = mFreeze ? 0.f : mtInfo.speed;

	if (mFreeze) mCurFreezeDelay += DT;

	GetAnimator()->Update();

	if (nullptr != mAI)
		mAI->Update();

	if (mCurFreezeDelay > mFreezeDelay) 
	{
		mFreeze = false;
		mCurFreezeDelay = 0.f;
		GetRigidBody()->SetKinematic(false);
	}

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
	if (mAI->GetCurStateType() == MONSTER_STATE::DEAD)
		return;

	mtInfo.curHp -= damage;

	if (mtInfo.curHp < 0)
	{
		ChangeAIState(mAI, MONSTER_STATE::DEAD);

		if (mHitSound)
			mHitSound->Play();
	}
	else if(mType != MONSTER_TYPE::BOSS)
	{
		if (mAI->GetCurStateType() != MONSTER_STATE::HIT)
		{
			ChangeAIState(mAI, MONSTER_STATE::HIT);

			if (mHitSound)
				mHitSound->Play();
		}
	}

	if (SettingMgr::GetI()->GetDamageTextActive())
	{
		//Vect2 vOff = Vect2((float)CRandom::GetI()->Next(-20, 20), (float)CRandom::GetI()->Next(-20, 20));

		CombatText* pCbTex = new CombatText;
		pCbTex->SetPos(GetLocalPos());
		pCbTex->SetText(std::to_wstring((int)damage));
		CreateObject(pCbTex, GROUP_TYPE::UI);
	}
}


void Monster::SetFreeze(float delay)
{
	if (mType == MONSTER_TYPE::BOSS) 
		return;

	mFreeze = true;
	mFreezeDelay = delay;
	mCurDamageDelay = 0.f;
	GetRigidBody()->SetKinematic(true);
}

void Monster::OnCollisionEnter(CCollider* _pOther)
{
	/*CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		tForce fc = {};
		fc.radius = 60.f;
		fc.force = 150.f;
		fc.speed = 2.5f;
		fc.pos = pOtherObj->GetLocalPos() - (GetLocalPos() - pOtherObj->GetLocalPos()).Normalize() * 3.f;

		CreateForce(fc);
	}*/
}

void Monster::OnCollisionStay(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player"
		&& mCurDamageDelay > 0.5f)
	{
		Player* player = PlayerMgr::GetI()->GetPlayer();

		player->AddDamage(mtInfo.atk);
		mCurDamageDelay = 0.f;
	}
}


void Monster::OnDestroy()
{
	DeleteObject(mHpBar);
}

