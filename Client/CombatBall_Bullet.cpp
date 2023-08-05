#include "pch.h"
#include "CombatBall_Bullet.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "PlayerMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "Player.h"
#include "Monster.h"
#include "Skill.h"




CombatBall_Bullet::CombatBall_Bullet()
	: mCurTime()
	, mRemainTime()
	, mArrivalTime(0.5f)
{
	SetMaxDelay(1.f);		// ��ų ���ӽð� ����
	SetDamageDelay(0.f);
	SetName(L"CombatBall_Bullet");
	CreateCollider();
	GetCollider()->SetScale(Vect2(20.f, 20.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CombatBall_Bullet", L"texture\\effect\\4.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"CombatBall_Bullet", pTex, Vect2(48.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.5f, 1);
	SetScale(Vect2(50.f, 50.f));

	GetAnimator()->Play(L"CombatBall_Bullet", true);
}

CombatBall_Bullet::~CombatBall_Bullet()
{
}


void CombatBall_Bullet::Update()
{
	if (mCurTime > GetMaxDelay())
	{
		DeleteObject(this);
		return;
	}

	mCurTime += DT / mArrivalTime;	// ������ ��� �����Ŵ
	mRemainTime = 1 - mCurTime;

	Vect2 V0 = mvStartPoint * mRemainTime + mvCurvePoint * mCurTime;
	Vect2 V1 = mvCurvePoint * mRemainTime + mvTarget * mCurTime;
	Vect2 V2 = V0 * mRemainTime + V1 * mCurTime;

	SetPos(V2);
	GetAnimator()->Update();
}

void CombatBall_Bullet::Render(HDC _dc)
{
	SkillObj::Render(_dc);

}

void CombatBall_Bullet::OnCollisionEnter(CCollider* _pOther) // �ʴ� ���ذ� �ƴ� ������ �ٷ� ���ظ� �ش�.
{
	CObject* pObj = _pOther->GetObj();
	Player* player = PlayerMgr::GetI()->GetPlayer();

	float damage = player->GetInfo().atkDamage;
	damage *= GetOwner()->GetSkillLevel();

	if (pObj->GetName() == L"Monster")		// ��ų ������Ʈ�� ���Ϳ� ������ �������� ����
	{
		((Monster*)pObj)->AddDamage(damage);
	}
}

void CombatBall_Bullet::OnCollisionStay(CCollider* _pOther)
{
}
