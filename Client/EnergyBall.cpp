#include "pch.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "CScene.h"

#include "EnergyBall.h"
#include "Player.h"
#include "EnergyBall_Obj.h"

EnergyBall::EnergyBall()
	: Skill(SKILL_TYPE::ENERGY_BALL, 5)
{
	SetIconStr(L"4.bmp");
	SetCoolDown(5.f);		// ��ų ��Ÿ�� ����
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::UseSkill()
{
	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);
	const vector<CObject*>& vecBoss = cscene->GetGroupObject(GROUP_TYPE::BOSS);

	if (vecMon.size() > 0)
	{
		EnergyBall_Obj* Ball = new EnergyBall_Obj;
		Ball->SetOwner(this);

		float length = 1000.f;
		Vect2 monsterPos;
		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			monsterPos = vecMon[i]->GetPos();
			if (length > (playerPos - monsterPos).Length())	// �÷��̾�� ������ ���̰� length ���� ���� �� (���� ����� ���� ã�´�)
			{
				length = (playerPos - monsterPos).Length(); // length �� �� ����
				mvDir = monsterPos - playerPos;
			}
		}

		mvDir.Normalize();
		Ball->SetDir(mvDir);
		Ball->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
		CreateObject(Ball, GROUP_TYPE::PROJ_PLAYER);
	}
	else if (vecBoss.size() > 0)
	{
		EnergyBall_Obj* Ball = new EnergyBall_Obj;
		Ball->SetOwner(this);

		Vect2 monsterPos = vecBoss[0]->GetPos();
		mvDir = (monsterPos - playerPos).Normalize();

		Ball->SetDir(mvDir);
		Ball->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
		CreateObject(Ball, GROUP_TYPE::PROJ_PLAYER);
	}


	SetSkillTime(0.f);
}

void EnergyBall::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // ��Ÿ���� ������ �ٽ� ��밡�� ���·� ����
	{
		SetAvailable(true);
	}
}

void EnergyBall::AddSkillLevel()
{
	Skill::AddSkillLevel();

	float newCoolDown = GetCoolDown() - 0.25 * GetSkillLevel();
	SetCoolDown(newCoolDown);
}
