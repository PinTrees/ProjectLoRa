#include "pch.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "CScene.h"

#include "Player.h"
#include "Thunder.h"
#include "Thunder_Obj.h"

#include "Random.h"


Thunder::Thunder()
	: Skill(SKILL_TYPE::THUNDER, 5)
{
	SetCoolDown(1.f);
}

Thunder::~Thunder()
{
}

void Thunder::UseSkill()
{
	SkillObj* pThunder = new Thunder_Obj;
	pThunder->SetOwner(this);

	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	vector<CObject*> vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

	float length = 1000.f;
	Vect2 monsterPos;

	int monIdx = CRandom::GetI()->Next(0, vecMon.size());
	pThunder->SetPos(vecMon[monIdx]->GetLocalPos());

	//for (size_t i = 0; i < vecMon.size(); ++i)
	//{
	//	monsterPos = vecMon[i]->GetLocalPos();
	//	if (length > (playerPos - monsterPos).Length())	// 플레이어와 몬스터의 길이가 length 보다 작을 때 (가장 가까운 적 찾기)
	//	{
	//		length = (playerPos - monsterPos).Length(); // length 에 값 대입
	//		pThunder->SetPos(monsterPos);
	//	}
	//}

	CreateObject(pThunder, GROUP_TYPE::PROJ_PLAYER);

	SetSkillTime(0.f);
}

void Thunder::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}