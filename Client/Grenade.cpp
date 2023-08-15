#include "pch.h"
#include "Grenade.h"
#include "Grenade_Obj.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "Player.h"
#include "CScene.h"




Grenade::Grenade()
	: Skill(SKILL_TYPE::GRENADE, /*6*/1)
{
	SetIconStr(L"6.bmp");
	SetCoolDown(4.f);
}

Grenade::~Grenade()
{
}

void Grenade::UseSkill()
{
	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);
	const vector<CObject*>& vecBoss = cscene->GetGroupObject(GROUP_TYPE::BOSS);

	Vect2 mvTarget = Vect2::zero;
	Vect2 curvPoint;

	if (vecMon.size() > 0)
	{
		float length = 1000.f;
		Vect2 monsterPos;

		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			monsterPos = vecMon[i]->GetPos();
			if (length > (playerPos - monsterPos).Length())	// �÷��̾�� ������ ���̰� length ���� ���� �� (���� ����� ���� ã�´�)
			{
				length = (playerPos - monsterPos).Length(); // length �� �� ����
				mvTarget = monsterPos;
			}
		}

		float curv_x = (mvTarget.x - playerPos.x) / 2.f;			// ���Ϳ� �÷��̾��� �߰��Ÿ��� ���Ѵ�.
		float curv_y = (mvTarget.y - playerPos.y) / 2.f - 500.f;	// ����ź�� ���� �� �� �������� �ϱ����� �߰��� 500.f �� ���ҽ�Ų��.

		curvPoint.x = playerPos.x + curv_x;		// Ŀ�� ������ ��ǥ�� ��´�.
		curvPoint.y = playerPos.y + curv_y;
	}
	else if (vecBoss.size() > 0)
	{
		mvTarget = vecBoss[0]->GetLocalPos();
		
		float curv_x = (mvTarget.x - playerPos.x) / 2.f;			// ���Ϳ� �÷��̾��� �߰��Ÿ��� ���Ѵ�.
		float curv_y = (mvTarget.y - playerPos.y) / 2.f - 500.f;	// ����ź�� ���� �� �� �������� �ϱ����� �߰��� 500.f �� ���ҽ�Ų��.

		curvPoint.x = playerPos.x + curv_x;		// Ŀ�� ������ ��ǥ�� ��´�.
		curvPoint.y = playerPos.y + curv_y;
	}


	if (mvTarget != Vect2::zero)
	{
		Grenade_Obj* grenade = new Grenade_Obj;

		grenade->SetOwner(this);
		grenade->SetStartPoint(playerPos);
		grenade->SetCurvePoint(curvPoint);
		grenade->SetTargetPoint(mvTarget);

		CreateObject(grenade, GROUP_TYPE::PROJ_PLAYER);
	}

	SetSkillTime(0.f);
}

void Grenade::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // ��Ÿ���� ������ �ٽ� ��밡�� ���·� ����
	{
		SetAvailable(true);
	}
}

void Grenade::AddSkillLevel()
{
	Skill::AddSkillLevel();

	float newCoolDown = GetCoolDown() - 0.2f * GetSkillLevel();
	SetCoolDown(newCoolDown);
}
