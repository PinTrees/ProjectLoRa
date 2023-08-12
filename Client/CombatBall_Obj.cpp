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
	Vect2 vDir = (vPlayer - GetPos()).Normalize();	// ������Ʈ�� �÷��̾������� �̵���Ű�� ���� ���Ⱚ�� ����

	SetPos(Vect2(GetPos() + vDir * DT * mSpeed));	// ������Ʈ�� õõ�� �̵���Ŵ
	mSpeed = 100.f;

	if (mCurTime > GetOwner()->GetCoolDown())	// �����ð����� �Ѿ��� ����
	{
		float Size = 300.f;		// �������� ���� Ŀ����ǥ ���� ������
		float Distance = 300.f;	// ������Ʈ���� �Ÿ�

		Vect2 LeftCurv = GetPos();
		LeftCurv.x += cosf(mTheta + 1.25f * PI) * Distance;	// ������Ʈ�� ���� �Ĺ��ʿ� Ŀ�������� ����
		LeftCurv.y += sinf(mTheta + 1.25f * PI) * Distance;

		Vect2 RightCurv = GetPos();
		RightCurv.x += cosf(mTheta + 0.75f * PI) * Distance; // ������Ʈ�� ���� �Ĺ��ʿ� Ŀ�������� ����
		RightCurv.y += sinf(mTheta + 0.75f * PI) * Distance;
		// ������ ��ǥ���� ������Ʈ�� ���ݹ���� �Բ� ȸ����

		// ���ʰ� ������ �����ư��� �Ѿ��� �ֵ��� ��         // ������ ������ ��ŭ���� �������� ��ǥ�� ����
		float Curv_x = mLeft ? (float)CRandom::GetI()->Next(int(LeftCurv.x - Size * 0.5f), int(LeftCurv.x + Size * 0.5f))
							 : (float)CRandom::GetI()->Next(int(RightCurv.x - Size * 0.5f), int(RightCurv.x + Size * 0.5f));
		float Curv_y = mLeft ? (float)CRandom::GetI()->Next(int(LeftCurv.y - Size * 0.5f), int(LeftCurv.y + Size * 0.5f))
							 : (float)CRandom::GetI()->Next(int(RightCurv.y - Size * 0.5f), int(RightCurv.y + Size * 0.5f));
		mLeft = !mLeft;

		Vect2 Pos = GetPos();			// ������Ʈ�� �����ϴ� ���� ��ǥ
		float Range = 380.f;			// ������Ʈ�� �����ϰ����ϴ� �Ÿ�

		Pos.x += cosf(mTheta) * Range;	// ������Ʈ�� ȸ���ϸ鼭 ������
		Pos.y += sinf(mTheta) * Range;

		Pos.x += CRandom::GetI()->Next(-50, 50);
		Pos.y += CRandom::GetI()->Next(-50, 50);

		CombatBall_Bullet* bullet = new CombatBall_Bullet;	// �Ѿ� ����

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