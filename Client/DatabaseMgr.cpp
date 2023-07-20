#include "pch.h"
#include "DatabaseMgr.h"

#include "IceBolt.h"


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
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_1] = new IceBolt;
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_2] = new IceBolt;
	mArrSkill[(UINT)SKILL_TYPE::TEST_SKILL_3] = new IceBolt;
}
