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
	// 복사 후 반환하는 형태로 변경
	return mArrSkill[(UINT)type];
}

void DatabaseMgr::Init()
{
	// 스킬은 다형성으로 구현
	// 각 스킬의 클래스에 직접 스킬의 사용 코드를 작성
	mArrSkill[(UINT)SKILL_TYPE::ICE_BOLT]		= new IceBolt;
	mArrSkill[(UINT)SKILL_TYPE::ENERGY_BALL]	= new EnergyBall;
	mArrSkill[(UINT)SKILL_TYPE::THUNDER]		= new Thunder;
	mArrSkill[(UINT)SKILL_TYPE::CIRCLING_BALL]	= new CirclingBall;
}
