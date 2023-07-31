#include "pch.h"
#include "Grenade.h"
#include "Grenade_Obj.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "Player.h"
#include "CScene.h"


Grenade::Grenade()
	: Skill(SKILL_TYPE::GRENADE, 6)
{
	SetCoolDown(4.f);
}

Grenade::~Grenade()
{
}

void Grenade::UseSkill()
{
	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	Vect2 playerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	vector<CObject*> vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

	float length = 1000.f;
	Vect2 monsterPos;
	Vect2 mvTarget;

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		monsterPos = vecMon[i]->GetPos();
		if (length > (playerPos - monsterPos).Length())	// 플레이어와 몬스터의 길이가 length 보다 작을 때 (가장 가까운 적을 찾는다)
		{
			length = (playerPos - monsterPos).Length(); // length 에 값 대입
			mvTarget = monsterPos;
		}
	}

	float curv_x = (mvTarget.x - playerPos.x) / 2.f;			// 몬스터와 플레이어의 중간거리를 구한다.
	float curv_y = (mvTarget.y - playerPos.y) / 2.f - 500.f;	// 수류탄이 높게 뜬 후 떨어지게 하기위해 추가로 500.f 를 감소시킨다.

	Vect2 curvPoint;
	curvPoint.x = playerPos.x + curv_x;		// 커브 지점의 좌표를 찍는다.
	curvPoint.y = playerPos.y + curv_y;

	Grenade_Obj* grenade = new Grenade_Obj;

	grenade->SetOwner(this);
	grenade->SetStartPoint(playerPos);
	grenade->SetCurvePoint(curvPoint);
	grenade->SetTargetPoint(mvTarget);

	CreateObject(grenade, GROUP_TYPE::PROJ_PLAYER);

	SetSkillTime(0.f);
}

void Grenade::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // 쿨타임이 끝나면 다시 사용가능 상태로 세팅
	{
		SetAvailable(true);
	}
}
