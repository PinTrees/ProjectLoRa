#include "pch.h"
#include "CrossDagger.h"
#include "CrossDagger_Obj.h"

#include "Player.h"
#include "PlayerMgr.h"

CrossDagger::CrossDagger()
	: Skill(SKILL_TYPE::CROSS_DAGGER, 5)
	, mCount(4)
{
	SetCoolDown(3.f);
}

CrossDagger::~CrossDagger()
{
}


void CrossDagger::UseSkill()
{
	float Theta;
	Theta = 2 * PI / mCount;

	for (int i = 0; i < mCount; ++i)		// ������ ������ŭ ǥâ ����
	{
		CrossDagger_Obj* pDagger = new CrossDagger_Obj;
		pDagger->SetOwner(this);
		pDagger->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
		pDagger->SetTheta(Theta * i);		// ǥâ�� ������ �����ϵ��� ���

		CreateObject(pDagger, GROUP_TYPE::PROJ_PLAYER);
	}
	
	SetSkillTime(0.f);
}

void CrossDagger::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // ��Ÿ���� ������ �ٽ� ��밡�� ���·� ����
	{
		SetAvailable(true);
	}
}