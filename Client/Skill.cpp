#include "pch.h"
#include "Skill.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "Bullet.h"




Skill::Skill(SKILL_TYPE type, int _maxLv)
	: mType(type)
	, mCooldown()
	, mUseCount()
	, mMaxSkillLv(_maxLv)
	, mCurSkillLv()
	, mAvailable(true)
	, mSkillTime()
{
}

Skill::~Skill()
{
}

void Skill::Update()
{
	mSkillTime += DT;		// 스킬을 사용한 후의 시간 (쿨타임과 비교하기 위해 사용)
}

void Skill::UseSkill()
{
	// 스킬 구현
}

void Skill::CheckAvailable()
{
	// 스킬 사용 조건 체크
}


void Skill::AddSkillLevel()
{
	if (mCurSkillLv < mMaxSkillLv)
		++mCurSkillLv;
}
