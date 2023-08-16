#include "pch.h"
#include "Boss.h"
#include "CCollider.h"
#include "Environment.h"
#include "Monster.h"
#include "CScene_start.h"

#include "CCore.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "PlayerMgr.h"
#include "CSceneMgr.h"
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
{
	tMonsterInfo info = {};
	info.atk = 100.f;
	info.atkRange = 100.f;
	info.curHp = info.hp = 5000.f;
	info.speed = 75.f;

	mtInfo = info;

	CreateCollider();
	CreateAnimator();

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Boss_1_r", L"texture\\monster\\boss_r.bmp");
	CTexture* pTex_l = CResMgr::GetI()->LoadTexture(L"Boss_1_l", L"texture\\monster\\boss_l.bmp");

	Vect2 vLeftTop = Vect2(0.f, 200.f);
	Vect2 vSliseSize = Vect2(200.f, 200.f);
	Vect2 vStepSize = Vect2(200.f, 0.f);
	Vect2 vRtPos = Vect2(2000.f, 200.f);

	GetAnimator()->CreateAnimation(L"IDLE_R", pTex, vLeftTop * 0.f, vSliseSize, vStepSize, 0.07f, 10);
	GetAnimator()->CreateAnimation(L"RUN_R", pTex, vLeftTop * 1.f, vSliseSize, vStepSize, 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DEAD_R", pTex, vLeftTop * 2.f, vSliseSize, vStepSize, 0.07f, 10);
	GetAnimator()->CreateAnimation(L"ATK_R", pTex, vLeftTop * 3.f, vSliseSize, vStepSize, 0.07f, 6);

	GetAnimator()->CreateAnimation(L"IDLE_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 0.f), vSliseSize, vStepSize * -1.f, 0.07f, 10);
	GetAnimator()->CreateAnimation(L"RUN_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 1.f), vSliseSize, vStepSize * -1.f, 0.07f, 8);
	GetAnimator()->CreateAnimation(L"DEAD_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 2.f), vSliseSize, vStepSize * -1.f, 0.07f, 10);
	GetAnimator()->CreateAnimation(L"ATK_L", pTex_l, Vect2(vRtPos.x - vStepSize.x, vRtPos.y * 3.f), vSliseSize, vStepSize * -1.f, 0.07f, 6);

	GetAnimator()->Play(L"RUN", true);

	float scaleFactor = 0.65f;

	GetCollider()->SetScale(Vect2(150.f, 150.f) * scaleFactor);
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f) * scaleFactor);
	
	SetScale(vSliseSize * 4.5f * scaleFactor);
	SetPivot(Vect2(0.f, 100.f) * scaleFactor);

	mvShadowScale = Vect2(220.f, 100.f) * scaleFactor;
	mvShadowOffset = Vect2(0.f, 125.f) * scaleFactor;

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
	DeleteObject(mpHpUI);
}



void Boss::Update()
{
	GetAnimator()->Update();

	mpHpBar->SetFilledAmount(mtInfo.curHp / mtInfo.hp);

	if (GetAI())
	{
		GetAI()->Update();
	}

	if (GetAI()->GetCurStateType() == MONSTER_STATE::DEAD)
	{
		CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();
		((Scene_Start*)pCurScene)->SetClear(true);
		return;
	}

	if (mtInfo.curHp < 0 && GetAI()->GetCurStateType() != MONSTER_STATE::DEAD)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
}

void Boss::Render(HDC dc)
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