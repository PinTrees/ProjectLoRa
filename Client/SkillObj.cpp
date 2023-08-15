#include "pch.h"

#include "PlayerMgr.h"
#include "CTimeMgr.h"

#include "Skill.h"
#include "SkillObj.h"
#include "CCollider.h"

#include "Player.h"
#include "Monster.h"
#include "CAnimator.h"


SkillObj::SkillObj()
	: mpOwner(nullptr)
	, mDamageDelay()
	, mCurDamageDelay()
	, mDamageCount()
	, mCurDamageCount()
	, mMaxDelay()
{
}

SkillObj::~SkillObj()
{
}

void SkillObj::Update()
{

}

void SkillObj::Render(HDC _dc)
{
	CompnentRender(_dc);
}

void SkillObj::OnCollisionEnter(CCollider* _pOther)
{
}

void SkillObj::OnCollisionStay(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	Player* player = PlayerMgr::GetI()->GetPlayer();

	float damage = player->GetInfo().atkDamage * 0.5f + (float)GetOwner()->GetSkillLevel() * mDamage * 0.5f;
	damage *= mpOwner->GetSkillLevel();

	if (pObj->GetName() == L"Monster")			// 스킬 오브젝트가 몬스터와 만나면 데미지를 입힘
	{
		mCurDamageDelay += DT;

		if (mCurDamageDelay >= mDamageDelay)
		{
			((Monster*)pObj)->AddDamage(damage);
			mCurDamageDelay = 0.f;
		}
	}
}
