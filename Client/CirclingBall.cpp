#include "pch.h"
#include "CirclingBall.h"

#include "PlayerMgr.h"

#include "Player.h"
#include "CirclingBall_Obj.h"

CirclingBall::CirclingBall()
	: Skill(SKILL_TYPE::CIRCLING_BALL, 5)
	, mPrevLv(1)
{
	SetCoolDown(0.f);		// ��Ÿ�� ����
}

CirclingBall::~CirclingBall()
{
}


void CirclingBall::UseSkill()
{
	float Theta;
	Theta = 2 * PI / GetSkillLevel();			// ������ ���� ���� ������ �����ϴµ� ���� ��ġ�� �����ϰ� ��� ���� ��

	for (int i = 0; i < GetSkillLevel(); ++i)
	{
		CirclingBall_Obj* pBall = new CirclingBall_Obj;		// ���� �� ��ŭ ���� ����
		pBall->SetOwner(this);
		pBall->SetTheta(Theta * i);
		pBall->SetPrevLv(GetSkillLevel());

		CreateObject(pBall, GROUP_TYPE::PROJ_PLAYER);
	}
}

void CirclingBall::CheckAvailable()
{
	if (mPrevLv < GetSkillLevel())		// �������� �ϸ� �ٷ� ���� ���� �����ǵ��� �ϱ����� ��밡�ɻ��·� ����
	{
		SetAvailable(true);
		mPrevLv = GetSkillLevel();
	}
}