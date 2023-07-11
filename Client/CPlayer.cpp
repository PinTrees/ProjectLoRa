#include "pch.h"
#include "CPlayer.h"

#include "CCore.h"

// Include Manager Header
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "Random.h"

// Include Component Header
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "RigidBody.h"

#include "CScene.h"
#include "CMissile.h"
#include "Bullet.h"
#include "Gun.h"

#include "HpBar.h"


Player::Player()
	: mfCurDelay(0.f)
	, mfDelay(0.03f)
	, mState(PLAYER_STATE::NONE)
	, mvDashDir(Vec2(0.f, 0.f))
	, mCurGun(nullptr)
	, mExpBar(nullptr)
	, mLevel(0)
	, mExp(0.f)
{
	// Init Object Component
	// Create Collider Component
	CreateCollider();
	GetCollider()->SetOffsetPos(GetPivot() - Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(40.f, 35.f));

	// Create RigidBody Component
	CreateRigidBody();
	GetRigidBody()->SetMess(1.f);
	GetRigidBody()->SetMaxVelocity(Vec2(200.f, 200.f));
	GetRigidBody()->SetAccelAlpha(Vec2(100.f, 100.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\character.bmp");

	// Create Animator Component
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"RUN_R", pTex, Vec2(0.f, 54.f * 2), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN_L", pTex, Vec2(0.f, 54.f * 30), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK_R", pTex, Vec2(0.f, 54.f * 14), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"ATK_L", pTex, Vec2(0.f, 54.f * 31), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"DASH_R", pTex, Vec2(0.f, 54.f * 23), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 7);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_R")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_L")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_L")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_R")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"DASH_R")->SetAllFrameOffet(Vec2(0.f, -20.f));

	GetAnimator()->Play(L"IDLE", true);

	SetScale(Vec2(73.f, 54.f) * 2.5f);
	SetPivot(Vec2(-30.f, 35.f));
	SetAlpha(100);

	mCurGun = new Gun(L"1");
	mCurGun->SetOwner(this);
	CreateObject(mCurGun, GROUP_TYPE::PLAYER);

	Vec2 vRes = CCore::GetI()->GetResolution();

	mExpBar = new BarUI;
	mExpBar->SetCameraAffected(true);
	mExpBar->SetScale(Vec2(vRes.x, 6.f));
	mExpBar->SetPos(Vec2(vRes.x * 0.5f, vRes.y - mExpBar->GetScale().y * 0.5f));
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
	
	Vec2 vPos = GetPos();
	mExpBar->SetAmount(GetExp() / GetMaxExp());

	if (mState == PLAYER_STATE::Dash)
	{
		mCurGun->SetVisible(false);

		SetPos(vPos + mvDashDir * 1000.f * DT);

		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mCurGun->SetVisible(true);
			mState = PLAYER_STATE::Idle;
		}

		return;
	}

	if (mCurGun != nullptr)
	{
		Vec2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
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

	if (KEY_HOLD(KEY::RBTN) && mfCurDelay > 0.01f)
	{
		mfCurDelay = 0.f;

		for (int i = 0; i < 2; ++i)
		{
			createMissile();
		}

		Vec2 pos = CCamera::GetI()->GetRealPos(MOUSE_POS);
		GetAnimator()->Play(pos.x > GetLocalPos().x ? L"ATK_R" : L"ATK_L", false);

		mState = PLAYER_STATE::ATTACK;
	}

	if (mState == PLAYER_STATE::ATTACK)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mState = PLAYER_STATE::Idle;
		}
	}

	else if (mState == PLAYER_STATE::Idle)
	{
		GetAnimator()->Play(L"IDLE", true);
	}

	Vec2 vDir = Vec2::zero;
	Vec2 vStartDir = Vec2::zero;

	if (KEY_HOLD(KEY::W)) vDir += Vec2::up;
	if (KEY_HOLD(KEY::S)) vDir += Vec2::down;
	if (KEY_HOLD(KEY::A)) vDir += Vec2::left;
	if (KEY_HOLD(KEY::D)) vDir += Vec2::right;

	if (vDir != Vec2::zero)
	{
		mState = PLAYER_STATE::Run;
		SetPos(vPos + vDir * 250.f * DT);

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
		mState = PLAYER_STATE::Idle;
	}
}

void Player::Render(HDC _dc)
{
	//컴포넌트 ( 충돌체 , ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}

void Player::createMissile()
{
	Vec2 vMissilePos = GetLocalPos() + Vec2(0.f, -50.f);

	Vec2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
	vDir.Normalize();

	// 일정 발사각 범위 내의 랜덤한 방향을 생성합니다.
	int launchAngle = 30;
	float angle = (float)CRandom::GetI()->Next(-15, 15); // -30도부터 30도 사이의 랜덤한 각도
	vDir.Rotate(angle); // 방향 벡터를 해당 각도만큼 회전시킵니다.

	// Missile Object
	Bullet* pMissile = new Bullet(L"3");
	pMissile->SetPos(vMissilePos + vDir.Normalize() * 50.f);
	pMissile->SetDir(vDir);
	pMissile->SetName(L"Missile_Player");

	//*** setPos setScale 는 인자로 받아서 설정하게 수정필요
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


