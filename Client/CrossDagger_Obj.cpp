#include "pch.h"
#include "CrossDagger_Obj.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "PlayerMgr.h"

#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include "CCollider.h"
#include "CAnimator.h"




CrossDagger_Obj::CrossDagger_Obj()
	: mCurTime()
	, mTheta()
	, mObjAngle()
{
	SetMaxDelay(2.f);
	SetDamage(7.f);
	SetName(L"CrossDagger");
	CreateCollider();
	GetCollider()->SetScale(Vect2(30.f, 30.f) * 1.5f);
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CrossDagger", L"texture\\effect\\6.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"CrossDagger", pTex, Vect2(36.f, 0.f), Vect2(36.f, 36.f), Vect2(36.f, 0.f), 0.5f, 1);
	SetScale(Vect2(50.f, 50.f) * 1.2f);

	GetAnimator()->Play(L"CrossDagger", true);
}

CrossDagger_Obj::~CrossDagger_Obj()
{
}

void CrossDagger_Obj::Update()
{
	if (mCurTime > GetMaxDelay())
	{
		DeleteObject(this);
		return;
	}

	Vect2 vPos = GetPos();

	vPos.x += cosf(mTheta) * 400.f * DT;		// ���ص� ����(���ص� ����)�� ���� ǥâ�� �̵��Ѵ�.
	vPos.y += sinf(mTheta) * 400.f * DT;

	SetPos(vPos);
	SetAngle(mObjAngle);		// ������Ʈ�� ȸ���ϵ��� ��
	GetAnimator()->Update();

	mCurTime += DT;
	mObjAngle += 500 * DT;
}

void CrossDagger_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}

void CrossDagger_Obj::OnCollisionEnter(CCollider* _pOther)	// �ʸ��� ���ظ� ������ ���� �ƴ� �ѹ� ���� ������ �������� ������ �Ѵ�.
{
	CObject* pObj = _pOther->GetObj();
	Player* player = PlayerMgr::GetI()->GetPlayer();

	float damage = player->GetInfo().atkDamage * 0.5f + (float)GetOwner()->GetSkillLevel() * GetDamage() * 0.5f;
	damage *= GetOwner()->GetSkillLevel();

	if (pObj->GetName() == L"Monster")		// ��ų ������Ʈ�� ���Ϳ� ������ �������� ����
	{
		((Monster*)pObj)->AddDamage(damage);
	}
}
