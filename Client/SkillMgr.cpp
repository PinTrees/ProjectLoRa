#include "pch.h"
#include "SkillMgr.h"

#include "Skill.h"
#include "EnergyBall.h"
#include "Thunder.h"
#include "CirclingBall.h"


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
	mArrSkill[(UINT)SKILL_TYPE::ENERGY_BALL] = new EnergyBall;
	mArrSkill[(UINT)SKILL_TYPE::THUNDER] = new Thunder;
	mArrSkill[(UINT)SKILL_TYPE::CIRCLING_BALL] = new CirclingBall;
}
