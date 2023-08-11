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
	SetCoolDown(5.f);		// 스킬 쿨타임 세팅
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::UseSkill()
{
	EnergyBall_Obj* Ball = new EnergyBall_Obj;
	Ball->SetOwner(this);

	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

	float length = 1000.f;
	Vect2 monsterPos;
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		monsterPos = vecMon[i]->GetPos();
		if (length > (playerPos - monsterPos).Length())	// 플레이어와 몬스터의 길이가 length 보다 작을 때 (가장 가까운 적을 찾는다)
		{
			length = (playerPos - monsterPos).Length(); // length 에 값 대입
			mvDir = monsterPos - playerPos;
		}
	}

	mvDir.Normalize();
	Ball->SetDir(mvDir);
	Ball->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
	CreateObject(Ball, GROUP_TYPE::PROJ_PLAYER);

	SetSkillTime(0.f);
}

void EnergyBall::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // 쿨타임이 끝나면 다시 사용가능 상태로 세팅
	{
		SetAvailable(true);
	}
}