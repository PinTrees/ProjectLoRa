#include "pch.h"
#include "Boomerang.h"
#include "Boomerang_Obj.h"

#include "PlayerMgr.h"
#include "CSceneMgr.h"

#include "Player.h"
#include "CScene.h"

#include "CSound.h"
#include "CResMgr.h"


Boomerang::Boomerang()
	: Skill(SKILL_TYPE::BOOMERANG, 6)
{
	SetIconStr(L"8.bmp");
	SetCoolDown(2.f);

	mpSound = CResMgr::GetI()->LoadSound(L"Skill_8", L"sound\\skill\\8.wav");
}

Boomerang::~Boomerang()
{
}


void Boomerang::UseSkill()
{
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);
	const vector<CObject*>& vecBoss = cscene->GetGroupObject(GROUP_TYPE::BOSS);

	Vect2 vDir = Vect2::zero;

	if (vecMon.size() > 0)
	{
		float length = 1000.f;
		Vect2 monsterPos;
		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			monsterPos = vecMon[i]->GetPos();
			if (length > (playerPos - monsterPos).Length())	// 플레이어와 몬스터의 길이가 length 보다 작을 때 (가장 가까운 적을 찾는다)
			{
				length = (playerPos - monsterPos).Length(); // length 에 값 대입
				vDir = monsterPos - playerPos;
			}
		}
		vDir.Normalize();
	}
	else if (vecBoss.size() > 0)
	{
		vDir = vecBoss[0]->GetPos() - playerPos;
		vDir.Normalize();
	}

	if (vDir != Vect2::zero)
	{
		Boomerang_Obj* boomerang = new Boomerang_Obj;
		boomerang->SetDir(vDir);
		boomerang->SetOwner(this);
		boomerang->SetPos(vPlayerPos);

		CreateObject(boomerang, GROUP_TYPE::PROJ_PLAYER);

		if (mpSound)
			mpSound->Play();
	}

	SetSkillTime(0.f);
}

void Boomerang::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}