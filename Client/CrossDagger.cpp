#include "pch.h"
#include "CrossDagger.h"
#include "CrossDagger_Obj.h"

#include "Player.h"
#include "PlayerMgr.h"




CrossDagger::CrossDagger()
	: Skill(SKILL_TYPE::CROSS_DAGGER, 8)
	, mCount(4)
{
	SetIconStr(L"7.bmp");
	SetCoolDown(3.f);
}

CrossDagger::~CrossDagger()
{
}


void CrossDagger::UseSkill()
{
	float Theta;
	int count = mCount + GetSkillLevel() - 1;
	Theta = 2 * PI / count;

	for (int i = 0; i < count; ++i)		// ������ ������ŭ ǥâ ����
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