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

	vPos.x += cosf(mTheta) * 400.f * DT;		// 정해둔 각도(정해둔 방향)에 따라 표창이 이동한다.
	vPos.y += sinf(mTheta) * 400.f * DT;

	SetPos(vPos);
	SetAngle(mObjAngle);		// 오브젝트가 회전하도록 함
	GetAnimator()->Update();

	mCurTime += DT;
	mObjAngle += 500 * DT;
}

void CrossDagger_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}

void CrossDagger_Obj::OnCollisionEnter(CCollider* _pOther)	// 초마다 피해를 입히는 것이 아닌 한번 맞을 때마다 데미지를 입히게 한다.
{
	CObject* pObj = _pOther->GetObj();
	Player* player = PlayerMgr::GetI()->GetPlayer();

	float damage = player->GetInfo().atkDamage * 0.5f + (float)GetOwner()->GetSkillLevel() * GetDamage() * 0.5f;
	damage *= GetOwner()->GetSkillLevel();

	if (pObj->GetName() == L"Monster")		// 스킬 오브젝트가 몬스터와 만나면 데미지를 입힘
	{
		((Monster*)pObj)->AddDamage(damage);
	}
}
