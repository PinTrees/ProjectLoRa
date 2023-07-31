#include "pch.h"
#include "Boomerang.h"
#include "Boomerang_Obj.h"

#include "PlayerMgr.h"
#include "CSceneMgr.h"

#include "Player.h"
#include "CScene.h"




Boomerang::Boomerang()
	: Skill(SKILL_TYPE::BOOMERANG, 6)
{
	SetCoolDown(2.f);
}

Boomerang::~Boomerang()
{
}


void Boomerang::UseSkill()
{
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	vector<CObject*> vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

	float length = 1000.f;
	Vect2 monsterPos;
	Vect2 vDir;
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		monsterPos = vecMon[i]->GetPos();
		if (length > (playerPos - monsterPos).Length())	// �÷��̾�� ������ ���̰� length ���� ���� �� (���� ����� ���� ã�´�)
		{
			length = (playerPos - monsterPos).Length(); // length �� �� ����
			vDir = monsterPos - playerPos;
		}
	}

	vDir.Normalize();

	Boomerang_Obj* boomerang = new Boomerang_Obj;
	boomerang->SetDir(vDir);
	boomerang->SetOwner(this);
	boomerang->SetPos(vPlayerPos);

	CreateObject(boomerang, GROUP_TYPE::PROJ_PLAYER);

	SetSkillTime(0.f);
}

void Boomerang::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}