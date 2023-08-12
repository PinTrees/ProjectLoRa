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
	, mSpeed(200.f)
	, mLeft(true)
{
	SetMaxDelay(0.f);
	SetName(L"CombatBall");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CombatBall", L"texture\\effect\\11.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.05f, 6);
	SetScale(Vect2(50.f, 50.f) * 1.5f);

	GetAnimator()->Play(L"IDLE", true);
}

CombatBall_Obj::~CombatBall_Obj()
{
}


void CombatBall_Obj::Update()
{
	mCurTime += DT;
	mTheta += 0.5f * DT;

	GetAnimator()->Update();

	if (mPrevLv > GetOwner()->GetSkillLevel())
	{
		DeleteObject(this);
		return;
	}

	Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetPos();
	Vect2 vDir = (vPlayer - GetPos()).Normalize();	// 오브젝트를 플레이어쪽으로 이동시키기 위해 방향값을 구함

	SetPos(Vect2(GetPos() + vDir * DT * mSpeed));	// 오브젝트를 천천히 이동시킴
	mSpeed = 100.f;

	if (mCurTime > GetOwner()->GetCoolDown())	// 일정시간마다 총알을 생성
	{
		float Size = 300.f;		// 랜덤으로 받을 커브좌표 값의 사이즈
		float Distance = 300.f;	// 오브젝트와의 거리

		Vect2 LeftCurv = GetPos();
		LeftCurv.x += cosf(mTheta + 1.25f * PI) * Distance;	// 오브젝트의 좌측 후방쪽에 커브지점을 생성
		LeftCurv.y += sinf(mTheta + 1.25f * PI) * Distance;

		Vect2 RightCurv = GetPos();
		RightCurv.x += cosf(mTheta + 0.75f * PI) * Distance; // 오브젝트의 우측 후방쪽에 커브지점을 생성
		RightCurv.y += sinf(mTheta + 0.75f * PI) * Distance;
		// 생성된 좌표들이 오브젝트의 공격방향과 함께 회전함

		// 왼쪽과 오른쪽 번갈아가며 총알이 휘도록 함         // 일정한 사이즈 만큼에서 랜덤으로 좌표를 받음
		float Curv_x = mLeft ? (float)CRandom::GetI()->Next(int(LeftCurv.x - Size * 0.5f), int(LeftCurv.x + Size * 0.5f))
							 : (float)CRandom::GetI()->Next(int(RightCurv.x - Size * 0.5f), int(RightCurv.x + Size * 0.5f));
		float Curv_y = mLeft ? (float)CRandom::GetI()->Next(int(LeftCurv.y - Size * 0.5f), int(LeftCurv.y + Size * 0.5f))
							 : (float)CRandom::GetI()->Next(int(RightCurv.y - Size * 0.5f), int(RightCurv.y + Size * 0.5f));
		mLeft = !mLeft;

		Vect2 Pos = GetPos();			// 오브젝트가 공격하는 곳의 좌표
		float Range = 380.f;			// 오브젝트가 공격하고자하는 거리

		Pos.x += cosf(mTheta) * Range;	// 오브젝트가 회전하면서 공격함
		Pos.y += sinf(mTheta) * Range;

		Pos.x += CRandom::GetI()->Next(-50, 50);
		Pos.y += CRandom::GetI()->Next(-50, 50);

		CombatBall_Bullet* bullet = new CombatBall_Bullet;	// 총알 생성

		bullet->SetOwner(GetOwner());
		bullet->SetPos(GetPos());
		bullet->SetStartPoint(GetPos());
		bullet->SetTarget(Pos);
		bullet->SetCurvePoint(Vect2(Curv_x, Curv_y));
		CreateObject(bullet, GROUP_TYPE::PROJ_PLAYER);

		mCurTime = GetOwner()->GetCoolDown() * 0.85f * GetOwner()->GetSkillLevel() / GetOwner()->GetMaxSkillLv();
	}
}

void CombatBall_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}