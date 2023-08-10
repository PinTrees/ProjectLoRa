#include "pch.h"
#include "CombatBall_Obj.h"
#include "CombatBall.h"
#include "CombatBall_Bullet.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "PlayerMgr.h"
#include "CSceneMgr.h"
#include "Random.h"

#include "CScene.h"
#include "Player.h"
#include "CAnimator.h"
#include "CCollider.h"




CombatBall_Obj::CombatBall_Obj()
	: mCurTime()
	, mPrevLv()
	, mTheta()
	, mSpeed(70.f)
	, mLeft(true)
{
	SetMaxDelay(0.f);
	SetName(L"CombatBall");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CombatBall", L"texture\\effect\\12.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(63.f, 75.f), Vect2(63.f, 0.f), 0.07f, 6);
	SetScale(Vect2(63.f, 75.f) * 1.5f);

	GetAnimator()->Play(L"IDLE", true);
}

CombatBall_Obj::~CombatBall_Obj()
{
}


void CombatBall_Obj::Update()
{
	if (mPrevLv > GetOwner()->GetSkillLevel())
	{
		DeleteObject(this);
		return;
	}

	Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetPos();

	Vect2 vDir = vPlayer - GetPos();	// 오브젝트를 플레이어쪽으로 이동시키기 위해 방향값을 구함
	vDir.Normalize();

	SetPos(Vect2(GetPos() + vDir * DT * mSpeed));	// 오브젝트를 천천히 이동시킴

	if ((vPlayer - GetPos()).Length() >= 150.f)	// 오브젝트와 플레이어의 걸이가 벌어지면
	{
		mSpeed = PlayerMgr::GetI()->GetPlayer()->GetInfo().moveSpeed;	// 오브젝트의 속도를 플레이어와 동일하게 줌
	}
	else
		mSpeed = 70.f;	// 아닐경우 속도를 복구시킴

	if (mCurTime > GetOwner()->GetCoolDown())	// 일정시간마다 총알을 생성
	{
		float Size = 200.f;		// 랜덤으로 받을 커브좌표 값의 사이즈
		float Distance = 300.f;	// 오브젝트와의 거리

		Vect2 LeftCurv = GetPos();
		LeftCurv.x += cosf(mTheta + 1.25f * PI) * Distance;	// 오브젝트의 좌측 후방쪽에 커브지점을 생성
		LeftCurv.y += sinf(mTheta + 1.25f * PI) * Distance;

		Vect2 RightCurv = GetPos();
		RightCurv.x += cosf(mTheta + 0.75f * PI) * Distance; // 오브젝트의 우측 후방쪽에 커브지점을 생성
		RightCurv.y += sinf(mTheta + 0.75f * PI) * Distance;
		// 생성된 좌표들이 오브젝트의 공격방향과 함께 회전함
		float Curv_x;
		float Curv_y;

		if (mLeft)		// 왼쪽과 오른쪽 번갈아가며 총알이 휘도록 함         // 일정한 사이즈 만큼에서 랜덤으로 좌표를 받음
		{
			Curv_x = (float)CRandom::GetI()->Next(int(LeftCurv.x - Size / 2.f), int(LeftCurv.x + Size / 2.f));
			Curv_y = (float)CRandom::GetI()->Next(int(LeftCurv.y - Size / 2.f), int(LeftCurv.y + Size / 2.f));
			mLeft = false;
		}
		else
		{
			Curv_x = (float)CRandom::GetI()->Next(int(RightCurv.x - Size / 2.f), int(RightCurv.x + Size / 2.f));
			Curv_y = (float)CRandom::GetI()->Next(int(RightCurv.y - Size / 2.f), int(RightCurv.y + Size / 2.f));
			mLeft = true;
		}

		Vect2 Pos = GetPos();			// 오브젝트가 공격하는 곳의 좌표
		float Range = 400.f;			// 오브젝트가 공격하고자하는 거리

		Pos.x += cosf(mTheta) * Range;	// 오브젝트가 회전하면서 공격함
		Pos.y += sinf(mTheta) * Range;

		CombatBall_Bullet* bullet = new CombatBall_Bullet;	// 총알 생성

		bullet->SetOwner(GetOwner());
		bullet->SetPos(GetPos());
		bullet->SetStartPoint(GetPos());
		bullet->SetTarget(Pos);
		bullet->SetCurvePoint(Vect2(Curv_x, Curv_y));

		CreateObject(bullet, GROUP_TYPE::PROJ_PLAYER);

		mCurTime = 0.f;
	}

	GetAnimator()->Update();

	mCurTime += DT;
	mTheta += 0.5f * DT;
}

void CombatBall_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}