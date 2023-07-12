#include "pch.h"
#include "Player.h"

#include "CCore.h"

// Include Manager Header
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "Random.h"
#include "UIMgr.h"

// Include Component Header
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "RigidBody.h"
#include "CScene.h"

// Include GameObject Header
#include "Bullet.h"
#include "Gun.h"

// Include UI Object Header
#include "CUI.h"
#include "BarUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "TextUI.h"




Player::Player()
	: mfCurDelay(0.f)
	, mfDelay(0.03f)
	, mState(PLAYER_STATE::NONE)
	, mvDashDir(Vect2(0.f, 0.f))
	, mCurGun(nullptr)
	, mExpBar(nullptr)
	, mLevel(0)
	, mExp(0.f)
	, mLevelupUI(nullptr)
{
	// Init Object Component
	// Create Collider Component
	CreateCollider();
	GetCollider()->SetOffsetPos(GetPivot() - Vect2(0.f, 15.f));
	GetCollider()->SetScale(Vect2(40.f, 35.f));

	// Create RigidBody Component
	CreateRigidBody();
	GetRigidBody()->SetMess(1.f);
	GetRigidBody()->SetMaxVelocity(Vect2(200.f, 200.f));
	GetRigidBody()->SetAccelAlpha(Vect2(100.f, 100.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\character.bmp");

	// Create Animator Component
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"RUN_R", pTex, Vect2(0.f, 54.f * 2), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN_L", pTex, Vect2(0.f, 54.f * 30), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK_R", pTex, Vect2(0.f, 54.f * 14), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"ATK_L", pTex, Vect2(0.f, 54.f * 31), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"DASH_R", pTex, Vect2(0.f, 54.f * 23), Vect2(73.f, 54.f), Vect2(73.f, 0.f), 0.05f, 7);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_R")->SetAllFrameOffet(Vect2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_L")->SetAllFrameOffet(Vect2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_L")->SetAllFrameOffet(Vect2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_R")->SetAllFrameOffet(Vect2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"DASH_R")->SetAllFrameOffet(Vect2(0.f, -20.f));

	GetAnimator()->Play(L"IDLE", true);

	SetScale(Vect2(73.f, 54.f) * 2.5f);
	SetPivot(Vect2(-30.f, 35.f));

	mCurGun = new Gun(L"1");
	mCurGun->SetOwner(this);
	CreateObject(mCurGun, GROUP_TYPE::PLAYER);

	Vect2 vRes = CCore::GetI()->GetResolution();

	mExpBar = new BarUI;
	mExpBar->SetCameraAffected(true);
	mExpBar->SetScale(Vect2(vRes.x, 6.f));
	mExpBar->SetPos(Vect2(vRes.x * 0.5f, vRes.y - mExpBar->GetScale().y * 0.5f));
	mExpBar->SetColor(RGB(255, 222, 0));
	CreateObject(mExpBar, GROUP_TYPE::UI);
}


Player::~Player()
{
}


void Player::Update()
{
	calExp();

	GetAnimator()->Update();

	mfCurDelay += DT;
	
	Vect2 vPos = GetPos();
	mExpBar->SetAmount(GetExp() / GetMaxExp());

	if (mState == PLAYER_STATE::Dash)
	{
		mCurGun->SetVisible(false);

		SetPos(vPos + mvDashDir * 1000.f * DT);

		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mCurGun->SetVisible(true);
			mState = PLAYER_STATE::IDLE;
		}

		return;
	}

	if (mCurGun != nullptr)
	{
		Vect2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
		mCurGun->SetAngle(vDir.ToAngle());
	}

	if (KEY_TAP(KEY::SPACE))
	{
		GetAnimator()->Play(L"DASH_R", false);

		mvDashDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
		mvDashDir.Normalize();

		mState = PLAYER_STATE::Dash;
		return;
	}

	if (KEY_HOLD(KEY::RBTN) && mfCurDelay > mCurGun->GetInfo().mReloadSpeed)
	{
		mfCurDelay = 0.f;

		for (int i = 0; i < 2; ++i)
		{
			createMissile();
		}

		Vect2 pos = CCamera::GetI()->GetRealPos(MOUSE_POS);
		GetAnimator()->Play(pos.x > GetLocalPos().x ? L"ATK_R" : L"ATK_L", false);

		mState = PLAYER_STATE::ATTACK;
	}

	if (mState == PLAYER_STATE::ATTACK)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mState = PLAYER_STATE::IDLE;
		}
	}

	else if (mState == PLAYER_STATE::IDLE)
	{
		GetAnimator()->Play(L"IDLE", true);
	}

	Vect2 vDir = Vect2::zero;

	if (KEY_HOLD(KEY::W)) vDir += Vect2::up;
	if (KEY_HOLD(KEY::S)) vDir += Vect2::down;
	if (KEY_HOLD(KEY::A)) vDir += Vect2::left;
	if (KEY_HOLD(KEY::D)) vDir += Vect2::right;

	if (vDir != Vect2::zero)
	{
		mState = PLAYER_STATE::Run;
		SetPos(vPos + vDir.Normalize() * 250.f * DT);

		if (vDir.x < 1)
		{
			GetAnimator()->Play(L"RUN_L", true);
		}
		else
		{
			GetAnimator()->Play(L"RUN_R", true);
		} 

		SetFlip(vDir.x < 1);
	}
	else
	{
		mState = PLAYER_STATE::IDLE;
	}
}

void Player::Render(HDC _dc)
{
	//컴포넌트 ( 충돌체, ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}

void Player::createMissile()
{
	Vect2 vMissilePos = GetLocalPos() + Vect2(0.f, -50.f);

	Vect2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
	vDir.Normalize();

	// 일정 발사각 범위 내의 랜덤한 방향을 생성합니다.
	int launchAngle = 30;
	float angle = (float)CRandom::GetI()->Next(-15, 15); // 랜덤한 각도
	vDir.Rotate(angle); // 방향 벡터를 해당 각도만큼 회전시킵니다.

	// 총알 오브젝트
	Bullet* pMissile = new Bullet(L"3");
	pMissile->SetPos(vMissilePos + vDir.Normalize() * 50.f);
	pMissile->SetDir(vDir);
	pMissile->SetName(L"Missile_Player");

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}



void Player::calExp()
{
	if (mExp >= GetMaxExp())
	{
		++mLevel;
		mExp = 0;

		Vect2 vRes = CCore::GetI()->GetResolution();

		mLevelupUI = new CPanelUI;
		mLevelupUI->SetPos(vRes * 0.5f);
		mLevelupUI->SetScale(vRes);
		CreateObject(mLevelupUI, GROUP_TYPE::UI);

		for (int i = 0; i < 3; ++i)
		{
			float spacing = vRes.x / 3;

			CPanelUI* pPanel = new CPanelUI;
			pPanel->SetPos(Vect2(spacing * i - spacing, 0.f));
			pPanel->SetScale(Vect2(300.f, 300.f));
			pPanel->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Panel_1", L"texture\\ui\\panel_1.bmp"));
			mLevelupUI->AddChild(pPanel);

			tUpgrad a = {};

			CBtnUI* pBtn = new CBtnUI;
			pBtn->SetPos(Vect2(0.f, 100.f));
			pBtn->SetScale(Vect2(200.f, 50.f));
			pBtn->SetText(L"선택");
			pBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
			pBtn->SetClickedCallBack(this, (OBJECT_FUNC_P)&Player::SelectLevelUp, (DWORD_PTR)&a);
			pPanel->AddChild(pBtn);
		}

		CTimeMgr::GetI()->Stop();
	}
}


void Player::SelectLevelUp(DWORD_PTR param)
{
	CTimeMgr::GetI()->Play();

	if (nullptr != mLevelupUI)
	{
		CUIMgr::GetI()->SetFocusUI(nullptr);
		DeleteObject(mLevelupUI);
	}
}
