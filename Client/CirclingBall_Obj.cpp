#include "pch.h"
#include "CirclingBall_Obj.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "PlayerMgr.h"

#include "Player.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "Skill.h"

CirclingBall_Obj::CirclingBall_Obj()
	: mTheta()
	, mPrevLv()
{
	SetMaxDelay(0.f);		// ��ų ���ӽð��� �ʿ� ���� ������ 0���� ����
	SetDamageDelay(0.2f);	// ~�ʸ��� �������� ����
	SetDamage(7.f);
	SetName(L"CirclingBall");
	
	CreateAnimator();
	CreateCollider();
	
	GetCollider()->SetScale(Vect2(40.f, 40.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CirclingBall", L"texture\\effect\\12.bmp");
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(63.f, 75.f), Vect2(63.f, 0.f), 0.07f, 6);
	SetScale(Vect2(63.f, 75.f) * 1.2f);

	GetAnimator()->Play(L"IDLE", true);
}

CirclingBall_Obj::~CirclingBall_Obj()
{
}

void CirclingBall_Obj::Update()
{
	if (mPrevLv < GetOwner()->GetSkillLevel())		// ���� ��ų ������ ���Ѵ�.
	{												// ��ų ������ ������ ���� �������� �Ѵ�. (������ ���缭 �ٽ� �����ϱ� ����)
		DeleteObject(this);
		return;
	}

	Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	Vect2 vPos;
	vPos.x = cosf(mTheta) * 100.f;
	vPos.y = sinf(mTheta) * 100.f;

	SetPos(vPos + vPlayer);			// ���� �÷��̾� �ֺ��� ���ۺ��� ������ �����Ѵ�.
	GetAnimator()->Update();

	mTheta += 2.5f * DT;

	if (mTheta >= 360.f)		// Theta ���� �ʹ� Ŀ���� �ʵ��� ��
		mTheta = 0.f;
}

void CirclingBall_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
