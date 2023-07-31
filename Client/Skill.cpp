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
	mSkillTime += DT;		// ��ų�� ����� ���� �ð� (��Ÿ�Ӱ� ���ϱ� ���� ���)
}

void Skill::UseSkill()
{
	// ��ų ����
}

void Skill::CheckAvailable()
{
	// ��ų ��� ���� üũ
}


void Skill::AddSkillLevel()
{
	if (mCurSkillLv < mMaxSkillLv)
		++mCurSkillLv;
}
