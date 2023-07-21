#include "pch.h"
#include "Skill.h"
#include "CKeyMgr.h"



Skill::Skill(SKILL_TYPE type, Skill_Func _skill, int _maxLv)
	: mType(type)
	, mIsActive()
	, mCooldown()
	, mUseCount()
	, mMaxSkillLv(_maxLv)
	, mCurSkillLv()
	, mSkillFunc(_skill)
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


void Skill::UseSkill()
{
	if (mSkillFunc)
	{
		mSkillFunc();
	}
}


void Skill::AddSkillLevel()
{
	if (mCurSkillLv < mMaxSkillLv)
		++mCurSkillLv;
}
