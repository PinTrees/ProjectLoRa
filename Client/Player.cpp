#include "pch.h"
#include "Player.h"

#include "CCore.h"

// Core Manager Header
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "Random.h"
#include "UIMgr.h"

// Component Header
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "RigidBody.h"
#include "CScene.h"

// GameObject Header
#include "Bullet.h"
#include "Gun.h"

#include "Skill.h"

// UI Object Header
#include "CUI.h"
#include "BarUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "TextUI.h"

#include "CState.h"

// Game Manager Header
#include "HubUIMgr.h"
#include "LevelUpUIMgr.h"



Player::Player()
	: mfCurDelay(0.f)
	, mfDelay(0.03f)
	, mvDir(Vect2(0.f, 0.f))
	, mCurGun(nullptr)
	, mExpBar(nullptr)
	, mLevel(0)
	, mExp(0.f)
	, mLevelupUI(nullptr)
	, mAI(nullptr)
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


	// Create Animator Component
	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player_idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_run_r.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_run_l.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_atk_r.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_atk_l.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_dash_r.anim");

	GetAnimator()->Play(L"IDLE", true);

	SetScale(Vect2(73.f, 54.f) * 1.7f);
	SetPivot(Vect2(-30.f, 35.f));

	mCurGun = new Gun(L"1");
	mCurGun->SetOwner(this);
	CreateObject(mCurGun, GROUP_TYPE::PLAYER);

	Vect2 vRes = CCore::GetI()->GetResolution();

	mExpBar = new BarUI;
	mExpBar->SetCameraAffected(true);
	mExpBar->SetScale(Vect2(vRes.x, 8.f));
	mExpBar->SetPos(Vect2(vRes.x * 0.5f, vRes.y - mExpBar->GetScale().y * 0.5f));
	mExpBar->SetColor(RGB(255, 222, 0));
	CreateObject(mExpBar, GROUP_TYPE::UI);

}


Player::~Player()
{
	if (nullptr != mAI)
		delete mAI;
}


void Player::Update()
{
	if (mAI)
		mAI->Update();
	GetAnimator()->Update();

	calExp();
	mfCurDelay += DT;
	
	Vect2 vPos = GetPos();
	mExpBar->SetAmount(GetExp() / GetMaxExp());

	if (mAI->GetCurStateType() == PLAYER_STATE::DASH)
		return;

	if (nullptr !=  mCurGun)
	{
		Vect2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
		mCurGun->SetAngle(vDir.ToAngle());
	}

	for (int i = 0; i < (UINT)LEVELUP_EFFECT::END - 12; ++i)
	{
		if (nullptr != mtPlayerInfo.mSkill[i])
			mtPlayerInfo.mSkill[i]->UseSkill();
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeAIState(GetAI(), PLAYER_STATE::DASH);
		return;
	}

	if (KEY_HOLD(KEY::RBTN)
		&& mfCurDelay >= mCurGun->GetInfo().shotDelay
		&& GetAI()->GetCurStateType() != PLAYER_STATE::ATTACK)
	{
		mfCurDelay = 0.f;
		ChangeAIState(GetAI(), PLAYER_STATE::ATTACK);
	}

	mvDir = Vect2::zero;

	if (KEY_HOLD(KEY::W)) mvDir += Vect2::up;
	if (KEY_HOLD(KEY::S)) mvDir += Vect2::down;
	if (KEY_HOLD(KEY::A)) mvDir += Vect2::left;
	if (KEY_HOLD(KEY::D)) mvDir += Vect2::right;

	if (mvDir != Vect2::zero)
	{
		if(GetAI()->GetCurStateType() != PLAYER_STATE::RUN)
			ChangeAIState(GetAI(), PLAYER_STATE::RUN);
	}
	else if(GetAI()->GetCurStateType() != PLAYER_STATE::IDLE
		&& GetAI()->GetCurStateType() != PLAYER_STATE::ATTACK)
	{
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void Player::Render(HDC _dc)
{
	//컴포넌트 ( 충돌체, ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}


void Player::calExp()
{
	if (mExp >= GetMaxExp())
	{
		++mLevel;
		mExp = 0;

		LevelupUIMgr::GetI()->Choice();
	}
}


