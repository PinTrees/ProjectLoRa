#include "pch.h"
#include "Boss.h"
#include "CCollider.h"
#include "Environment.h"
#include "Monster.h"

#include "CCore.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "PlayerMgr.h"
#include "Player.h"

#include "CTimeMgr.h"
#include "Particle.h"

#include "CImageUI.h"
#include "CColumn.h"
#include "TextUI.h"

#include "GUIMgr.h"


Boss::Boss(const wstring& uid)
	: Monster(MONSTER_TYPE::BOSS, L"999")
	, mpHpBar(nullptr)
	, mCurState(BOSS_STATE::TRACE)
{
	tMonsterInfo info = {};
	info.atk = 100.f;
	info.atkRange = 100.f;
	info.curHp = info.hp = 5000.f;
	info.speed = 75.f;

	mtInfo = info;

	CreateCollider();
	CreateAnimator();

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Boss_1", L"texture\\monster\\1.bmp");

	Vect2 vLeftTop = Vect2(0.f, 93.f);
	Vect2 vSliseSize = Vect2(140.f, 93.f);
	Vect2 vStepSize = Vect2(140.f, 0.f);

	GetAnimator()->CreateAnimation(L"IDLE", pTex, vLeftTop * 0.f, vSliseSize, vStepSize, 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN", pTex, vLeftTop * 1.f, vSliseSize, vStepSize, 0.1f, 8);
	GetAnimator()->CreateAnimation(L"ATK", pTex, vLeftTop * 2.f, vSliseSize, vStepSize, 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DEAD", pTex, vLeftTop * 4.f, vSliseSize, vStepSize, 0.07f, 7);
	GetAnimator()->CreateAnimation(L"CREATE", pTex, vLeftTop * 8.f, vSliseSize, vStepSize, 0.07f, 8);

	GetCollider()->SetScale(Vect2(100.f, 220.f));
	GetCollider()->SetOffsetPos(Vect2(170.f, 90.f));

	GetAnimator()->Play(L"RUN", true);

	SetScale(vSliseSize * 4.5f);
	SetPivot(Vect2(170.f, 130.f));


	Vect2 vRes = CCore::GetI()->GetResolution();

	mpHpUI = new CColumn;
	mpHpUI->SetPos(Vect2(vRes.x * 0.5f, 50.f));
	mpHpUI->SetScale(Vect2(350.f, 36.f));
	CreateObject(mpHpUI, GROUP_TYPE::UI);

	TextUI* pText = new TextUI;
	pText->SetScale(Vect2(0.f, 30.f));
	pText->SetFontSize(36.f);
	pText->SetOutlineWidth(2.f);
	pText->SetOutlineColor(RGB(0, 0, 0));
	pText->SetColor(RGB(255, 0, 0));
	pText->SetText(L"BOSS");
	mpHpUI->AddChild(pText);

	// HP Bar 
	CImageUI* pHpBarUI = new CImageUI;
	pHpBarUI->SetScale(Vect2(350.f, 40.f));
	pHpBarUI->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar_Background", L"texture\\ui\\hp_bar\\hp_background.bmp"));
	mpHpUI->AddChild(pHpBarUI);

	mpHpBar = new CImageUI;
	mpHpBar->SetScale(pHpBarUI->GetScale());
	mpHpBar->SetImageType(IMAGE_TYPE::FILLED);
	mpHpBar->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar_2", L"texture\\ui\\hp_bar\\hp_bar_2.bmp"));
	pHpBarUI->AddChild(mpHpBar);
	 
	CImageUI* pHpBarFrame = new CImageUI;
	pHpBarFrame->SetScale(pHpBarUI->GetScale());
	pHpBarFrame->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar_Frame", L"texture\\ui\\hp_bar\\hp_bar_frame.bmp"));
	//pHpBarUI->AddChild(pHpBarFrame);
}

Boss::~Boss()
{
}



void Boss::Update()
{
	GetAnimator()->Update();

	mpHpBar->SetFilledAmount(mtInfo.curHp / mtInfo.hp);

	if (mCurState == BOSS_STATE::DIE)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish()) {
			DeleteObject(this);
			DeleteObject(mpHpUI);

			GUIMgr::GetI()->ShowGameClearUI();
		}
		return;
	}

	if (mtInfo.curHp <= 0) {
		mCurState = BOSS_STATE::DIE;
		GetAnimator()->Play(L"DEAD", false);
	}

	Vect2 vLocalPos = GetLocalPos();
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();

	if (mCurState == BOSS_STATE::TRACE)
	{
		Vect2 vPos = GetPos();

		Vect2 vDir = pPlayer->GetLocalPos() - vLocalPos;
		vDir.Normalize();

		SetPos(vPos + vDir * DT * 75.f);

		if (Vect2::Distance(GetLocalPos(), pPlayer->GetLocalPos()) < mtInfo.atkRange)
		{
			mCurState = BOSS_STATE::ATK;
			GetAnimator()->Play(L"ATK", false);
		}
	}
	else if (mCurState == BOSS_STATE::ATK)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish()) {
			mCurState = BOSS_STATE::TRACE;
			GetAnimator()->Play(L"RUN", true);
		}
	}
}

void Boss::Render(HDC dc)
{
	CObject::CompnentRender(dc);
}


void Boss::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"ENV")
	{
		((Environment*)pOtherObj)->DistoryEnvi();

		Particle* pParticle = new Particle(L"2");
		pParticle->SetPos(pOtherObj->GetPos());
		pParticle->SetScale(pParticle->GetScale() * 2.2f);
		CreateObject(pParticle, GROUP_TYPE::EFFECT);
	}
}