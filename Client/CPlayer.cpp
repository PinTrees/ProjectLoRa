#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneMgr.h"


#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CMissile.h"
#include "Bullet.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
	: mfCurDelay(0.f)
	, mfDelay(0.03f)
	, mState(PLAYER_STATE::None)
	, mvDashDir(Vec2(0.f, 0.f))
{
	SetPivot(Vec2(-30.f, 35.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(GetPivot() - Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(40.f, 35.f));


	// Texture �ε��ϱ�
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\character.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"RUN_R", pTex, Vec2(0.f, 54.f * 2), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"RUN_L", pTex, Vec2(0.f, 54.f * 30), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK_R", pTex, Vec2(0.f, 54.f * 14), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"ATK_L", pTex, Vec2(0.f, 54.f * 31), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 3);
	GetAnimator()->CreateAnimation(L"DASH_R", pTex, Vec2(0.f, 54.f * 23), Vec2(73.f, 54.f), Vec2(73.f, 0.f), 0.05f, 7);

	GetAnimator()->Play(L"IDLE",true);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_R")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN_L")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_L")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK_R")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"DASH_R")->SetAllFrameOffet(Vec2(0.f, -20.f));

	SetScale(Vec2(73.f, 54.f) * 2.5f);
}


CPlayer::~CPlayer()
{

}


void CPlayer::Update()
{
	GetAnimator()->Update();

	mfCurDelay += fDT;
	Vec2 vPos = GetPos();
	Vec2 vDir = Vec2::zero;

	if (mState == PLAYER_STATE::Dash)
	{
		vPos += mvDashDir * 500.f * fDT;
		SetPos(vPos);

		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mState = PLAYER_STATE::Idle;
		}
		return;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		GetAnimator()->Play(L"DASH_R", false);

		mvDashDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
		mvDashDir.Normalize();

		mState = PLAYER_STATE::Dash;
		return;
	}

	if (KEY_HOLD(KEY::RBTN) && mfCurDelay > 0.05f)
	{
		mfCurDelay = 0.f;

		for (int i = 0; i < 2; ++i)
		{
			createMissile();
		}

		Vec2 pos = CCamera::GetI()->GetRealPos(MOUSE_POS);
		if (pos.x > vPos.x)
		{
			GetAnimator()->Play(L"ATK_R", false);
		}
		else
		{
			GetAnimator()->Play(L"ATK_L", false);
		}

		mState = PLAYER_STATE::Attack;
	}

	if (mState == PLAYER_STATE::Attack)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			mState = PLAYER_STATE::Idle;
		}
		return;
	}

	else if (mState == PLAYER_STATE::Idle)
	{
		GetAnimator()->Play(L"IDLE", true);
	}


	if (KEY_HOLD(KEY::W)) vDir = Vec2::up; 
	if (KEY_HOLD(KEY::S)) vDir += Vec2::down;
	if (KEY_HOLD(KEY::A)) vDir += Vec2::left;
	if (KEY_HOLD(KEY::D)) vDir += Vec2::right;


	if (vDir != Vec2::zero)
	{
		vPos += vDir * 200.f * fDT;
		mState = PLAYER_STATE::Run;

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
	
	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	//������Ʈ ( �浹ü , ect...	) �� �ִ°�� ����
	CompnentRender(_dc);
}

void CPlayer::createMissile()
{
	Vec2 vMissilePos = GetLocalPos() + Vec2(0.f, -50.f);

	Vec2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
	vDir.Normalize();

	// ���� �߻簢 ���� ���� ������ ������ �����մϴ�.
	int launchAngle = 30;
	float angle = (rand() % launchAngle) - launchAngle * 0.5f; // -30������ 30�� ������ ������ ����
	vDir.Rotate(angle); // ���� ���͸� �ش� ������ŭ ȸ����ŵ�ϴ�.

	// Missile Object
	Bullet* pMissile = new Bullet(L"3");
	pMissile->SetPos(vMissilePos);
	pMissile->SetDir(vDir);
	pMissile->SetName(L"Missile_Player");

	//*** setPos setScale �� ���ڷ� �޾Ƽ� �����ϰ� �����ʿ�
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


