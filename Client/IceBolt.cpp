#include "pch.h"
#include "IceBolt.h"



IceBolt::IceBolt()
	: Skill(SKILL_TYPE::TEST_SKILL_1, 10)
{
}

IceBolt::~IceBolt()
{
}


bool IceBolt::IsStart()
{
	if (Skill::IsCoolTimeOn())
	{
		return true;
	}

	return false;
}




void IceBolt::Start()
{

}

void IceBolt::ActiveUpdate()
{
}
