#include "pch.h"
#include "SkillMgr.h"

#include "Skill.h"


SINGLE_HEADER(SkillMgr);


SkillMgr::SkillMgr()
	: mArrSkill{}
{
}

SkillMgr::~SkillMgr()
{
	for (int i = 0; i < (UINT)SKILL_TYPE::END; ++i)
	{
		if (nullptr != mArrSkill[i])
			delete mArrSkill[i];
	}
}


Skill* SkillMgr::GetSkill(SKILL_TYPE type)
{
	// ���� �� ��ȯ�ϴ� ���·� ����
	return mArrSkill[(UINT)type];
}

void SkillMgr::Init()
{
	// ��ų�� ���������� ����
	// �� ��ų�� Ŭ������ ���� ��ų�� ��� �ڵ带 �ۼ�
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_1] = new Skill(SKILL_TYPE::TEST_SKILL_1, nullptr, 10);
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_2] = new Skill(SKILL_TYPE::TEST_SKILL_1, nullptr, 10);
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_3] = new Skill(SKILL_TYPE::TEST_SKILL_1, nullptr, 10);
}
