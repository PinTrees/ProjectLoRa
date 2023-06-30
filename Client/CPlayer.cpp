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
{
	SetPivot(Vec2(-30.f, 35.f));

	CreateCollider();
	GetCollider()->SetOffsetPos(GetPivot() - Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(40.f, 35.f));


	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"PlayerTex", L"texture\\character.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(73.f, 62.f), Vec2(73.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 54.f * 2), Vec2(73.f, 62.f), Vec2(73.f, 0.f), 0.07f, 8);
	GetAnimator()->CreateAnimation(L"ATK", pTex, Vec2(0.f, 54.f * 14), Vec2(73.f, 62.f), Vec2(73.f, 0.f), 0.1f, 3);
	GetAnimator()->Play(L"RUN",true);

	GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"RUN")->SetAllFrameOffet(Vec2(0.f, -20.f));
	GetAnimator()->FindAnimation(L"ATK")->SetAllFrameOffet(Vec2(0.f, -20.f));
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
	if (KEY_TAP(KEY::SPACE))
	{}

	if (vDir != Vec2::zero)
	{
		vPos += vDir * 200.f * fDT;
		GetAnimator()->Play(L"RUN", true);
		mState = PLAYER_STATE::Run;

		SetFlip(vDir.x < 1);
	}
	


	if (KEY_HOLD(KEY::RBTN) && mfCurDelay > mfDelay)
	{
		mfCurDelay = 0.f;

		for (int i = 0; i < 8; ++i)
		{
			createMissile();
		}

		GetAnimator()->Play(L"ATK", false);
		mState = PLAYER_STATE::Attack;
	}


	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	//컴포넌트 ( 충돌체 , ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}

void CPlayer::createMissile()
{
	Vec2 vMissilePos = GetLocalPos() + Vec2(0.f, -50.f);

	Vec2 vDir = CCamera::GetI()->GetRealPos(MOUSE_POS) - GetPos();
	vDir.Normalize();

	// 일정 발사각 범위 내의 랜덤한 방향을 생성합니다.
	float angle = (rand() % 30) - 15; // -30도부터 30도 사이의 랜덤한 각도
	vDir.Rotate(angle); // 방향 벡터를 해당 각도만큼 회전시킵니다.

	// Missile Object
	Bullet* pMissile = new Bullet(L"1");
	pMissile->SetPos(vMissilePos);
	pMissile->SetDir(vDir);
	pMissile->SetName(L"Missile_Player");

	//*** setPos setScale 는 인자로 받아서 설정하게 수정필요
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


