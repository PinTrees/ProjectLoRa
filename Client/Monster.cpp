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
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CScene.h"
#include "AI.h"
#include "Gold.h"

// Include UI
#include "BarUI.h"

#include "CombatText.h"
#include "SelectGDI.h"

#include "Player.h"

Monster::Monster(MONSTER_TYPE Type, const wstring uid)
	: mtInfo({})
	, mAI(nullptr)
	, mType(Type)
	, mCurDamageDelay()
	, mFreeze(false)
	, mOriginalSpeed()
{
	SetName(L"Monster");
	mtInfo.UID = uid;

	CreateCollider();
	CreateAnimator();

	mHpBar = new BarUI;
	mHpBar->SetScale(Vect2(40.f, 4.f));
	mHpBar->SetColor(RGB(255, 0, 0));
	CreateObject(mHpBar, GROUP_TYPE::UI);

	if (mtInfo.UID == L"3")
	{
		CTexture* pTex_r = CResMgr::GetI()->LoadTexture(L"Monster_3_r", L"texture\\monster\\3_r.bmp");

		Vect2 vSliseSize = Vect2(128.f, 130.f);
		Vect2 vStepSize = Vect2(128.f, 0.f);
		Vect2 vLtPos = Vect2(0.f, 130.f);

		GetAnimator()->CreateAnimation(L"IDLE", pTex_r, vLtPos * 0.f, vSliseSize, vStepSize, 0.07f, 8);
		GetAnimator()->CreateAnimation(L"RUN", pTex_r, vLtPos * 1.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"ATK", pTex_r, vLtPos * 3.f, vSliseSize, vStepSize, 0.07f, 7);
		GetAnimator()->CreateAnimation(L"DEAD", pTex_r, vLtPos * 9, vSliseSize, vStepSize, 0.07f, 4);
		//GetAnimator()->CreateAnimation(L"CREATE", pTex, Vect2(0.f, 93 * 8.f), vSliseSize, vStepSize, 0.07f, 8);
		GetCollider()->SetScale(Vect2(30.f, 50.f));
		GetCollider()->SetOffsetPos(Vect2(0.f, 25.f));
		SetScale(Vect2(128.f, 130.f) * 0.8f);
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));

		mHpBar->SetPivot(Vect2(0.f, -12.f));
	}
	else if (mtInfo.UID == L"2")
	{
		CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_2", L"texture\\monster\\2.bmp");

		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 48.f * 1.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"RUN", pTex, Vect2(0.f, 48.f * 3.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"ATK", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetAnimator()->CreateAnimation(L"DEAD", pTex, Vect2(0.f, 48.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.1f, 4);
		GetCollider()->SetOffsetPos(Vect2::zero);
		SetScale(Vect2(48.f, 48.f) * 1.f);
		SetPivot(Vect2(0.f, GetScale().y * 0.5f));
		GetCollider()->SetScale(GetScale() * 0.6f);

		mHpBar->SetPivot(Vect2(0.f, GetScale().y * -0.4f));
	}

	GetAnimator()->Play(L"IDLE", true);
}

Monster::~Monster()
{
	if (nullptr != mAI)
		delete mAI;
}


void Monster::Render(HDC dc)
{
	CompnentRender(dc);

	if (mVecPathPos.empty())
		return;

	SelectGDI p = SelectGDI(dc, PEN_TYPE::BLUE);

	if (DEBUG)
	{
		Vect2 vStartPos = CCamera::GetI()->GetRenderPos(mVecPathPos[0]);

		MoveToEx(dc, vStartPos.x, vStartPos.y, nullptr); // 현재 좌표 설정
		// 나머지 좌표들을 순회하며 라인을 그립니다.
		for (size_t i = 1; i < mVecPathPos.size(); ++i)
		{
			Vect2 vDrawPos = CCamera::GetI()->GetRenderPos(mVecPathPos[i]);
			LineTo(dc, vDrawPos.x, vDrawPos.y);
		}
	}
}


void Monster::Update()
{
	mCurDamageDelay += DT;

	GetAnimator()->Update();

	if (mFreeze)
	{
		mtInfo.curSpeed = 0.f;					// 얼어있는 상태면 현재 속도를 0으로 만듦.
	}
	else
	{
		mtInfo.curSpeed = mtInfo.speed;			// 몬스터의 이동속도를 curSpeed를 사용하여 이동시킴
	}

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

