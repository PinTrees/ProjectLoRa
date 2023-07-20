#include "pch.h"
#include "Skill.h"
#include "CKeyMgr.h"

#include "CTimeMgr.h"


Skill::Skill(SKILL_TYPE type, int _maxLv)
	: mUID(type)
	, mUseType(SKILL_USE_TYPE::ACTIVE)
	, mCoolDelay(0)
	, mCurDelay(0)
	, mIsActive(false)
	, mUseCount()
	, mMaxSkillLv(_maxLv)
	, mCurSkillLv()
{
}

Skill::~Skill()
{
}


void TestSkill()
{
	if (KEY_TAP(KEY::LBTN))
		int a = 0;
}


void Skill::Update()
{
	if (SKILL_USE_TYPE::ACTIVE == mUseType && !mIsActive)
	{
		mCurDelay += DT;
	}
}

bool Skill::IsCoolTimeOn()
{
	if (mIsActive)
		return false;

	if (mCurDelay >= mCoolDelay)
		return true;
	
	return false;
}



void Skill::AddSkillLevel()
{
	if (mCurSkillLv < mMaxSkillLv)
		++mCurSkillLv;
}
