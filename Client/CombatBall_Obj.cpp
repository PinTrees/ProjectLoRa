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

	Vect2 vDir = vPlayer - GetPos();	// ������Ʈ�� �÷��̾������� �̵���Ű�� ���� ���Ⱚ�� ����
	vDir.Normalize();

	SetPos(Vect2(GetPos() + vDir * DT * mSpeed));	// ������Ʈ�� õõ�� �̵���Ŵ

	if ((vPlayer - GetPos()).Length() >= 150.f)	// ������Ʈ�� �÷��̾��� ���̰� ��������
	{
		mSpeed = PlayerMgr::GetI()->GetPlayer()->GetInfo().moveSpeed;	// ������Ʈ�� �ӵ��� �÷��̾�� �����ϰ� ��
	}
	else
		mSpeed = 70.f;	// �ƴҰ�� �ӵ��� ������Ŵ

	if (mCurTime > GetOwner()->GetCoolDown())	// �����ð����� �Ѿ��� ����
	{
		float Size = 200.f;		// �������� ���� Ŀ����ǥ ���� ������
		float Distance = 300.f;	// ������Ʈ���� �Ÿ�

		Vect2 LeftCurv = GetPos();
		LeftCurv.x += cosf(mTheta + 1.25f * PI) * Distance;	// ������Ʈ�� ���� �Ĺ��ʿ� Ŀ�������� ����
		LeftCurv.y += sinf(mTheta + 1.25f * PI) * Distance;

		Vect2 RightCurv = GetPos();
		RightCurv.x += cosf(mTheta + 0.75f * PI) * Distance; // ������Ʈ�� ���� �Ĺ��ʿ� Ŀ�������� ����
		RightCurv.y += sinf(mTheta + 0.75f * PI) * Distance;
		// ������ ��ǥ���� ������Ʈ�� ���ݹ���� �Բ� ȸ����
		float Curv_x;
		float Curv_y;

		if (mLeft)		// ���ʰ� ������ �����ư��� �Ѿ��� �ֵ��� ��         // ������ ������ ��ŭ���� �������� ��ǥ�� ����
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

		Vect2 Pos = GetPos();			// ������Ʈ�� �����ϴ� ���� ��ǥ
		float Range = 400.f;			// ������Ʈ�� �����ϰ����ϴ� �Ÿ�

		Pos.x += cosf(mTheta) * Range;	// ������Ʈ�� ȸ���ϸ鼭 ������
		Pos.y += sinf(mTheta) * Range;

		CombatBall_Bullet* bullet = new CombatBall_Bullet;	// �Ѿ� ����

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