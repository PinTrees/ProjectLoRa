#include "pch.h"
#include "DatabaseMgr.h"

#include "Skill.h"
#include "IceBolt.h"
#include "EnergyBall.h"
#include "Thunder.h"
#include "CirclingBall.h"

SINGLE_HEADER(DatabaseMgr);


DatabaseMgr::DatabaseMgr()
{

}

DatabaseMgr::~DatabaseMgr()
{
	for (int i = 0; i < (UINT)SKILL_TYPE::END; ++i)
	{
		if (nullptr != mArrSkill[i])
			delete mArrSkill[i];
	}
}



Skill* DatabaseMgr::GetSkill(SKILL_TYPE type)
{
	// ���� �� ��ȯ�ϴ� ���·� ����
	return mArrSkill[(UINT)type];
}

void DatabaseMgr::Init()
{
	// ��ų�� ���������� ����
	// �� ��ų�� Ŭ������ ���� ��ų�� ��� �ڵ带 �ۼ�
	mArrSkill[(UINT)SKILL_TYPE::ICE_BOLT]		= new IceBolt;
	mArrSkill[(UINT)SKILL_TYPE::ENERGY_BALL]	= new EnergyBall;
	mArrSkill[(UINT)SKILL_TYPE::THUNDER]		= new Thunder;
	mArrSkill[(UINT)SKILL_TYPE::CIRCLING_BALL]	= new CirclingBall;
}
