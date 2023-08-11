#include "pch.h"

#include "IceBolt.h"
#include "IceBolt_Obj.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "CScene.h"

#include "Player.h"

 


IceBolt::IceBolt()
	: Skill(SKILL_TYPE::ICE_BOLT, 5)
{
	SetIconStr(L"2.bmp");
	SetCoolDown(3.f);
}

IceBolt::~IceBolt()
{
}

void IceBolt::UseSkill()
{
	IceBolt_Obj* Bolt = new IceBolt_Obj;
	Bolt->SetOwner(this);

	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	vector<CObject*> vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

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
	Bolt->SetDir(mvDir);
	Bolt->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
	Bolt->SetAngleOffset(mvDir.ToAngle());
	CreateObject(Bolt, GROUP_TYPE::PROJ_PLAYER);

	SetSkillTime(0.f);
}

void IceBolt::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}