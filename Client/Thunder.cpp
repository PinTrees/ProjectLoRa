#include "pch.h"

#include "CSceneMgr.h"
#include "PlayerMgr.h"

#include "CScene.h"

#include "Player.h"
#include "Thunder.h"
#include "Thunder_Obj.h"

#include "Random.h"
#include "CSound.h"
#include "CResMgr.h"


Thunder::Thunder()
	: Skill(SKILL_TYPE::THUNDER, 5)
{
	SetIconStr(L"2.bmp");
	SetCoolDown(1.f);

	mThunderSound = CResMgr::GetI()->LoadSound(L"Sound_Skill_2", L"sound\\skill\\2.wav");
	mThunderSound->SetVolumeOffset(500);
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

	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);

	float length = 1000.f;
	Vect2 monsterPos;

	int monIdx = CRandom::GetI()->Next(0, vecMon.size());

	if (vecMon.size() > 0)
		pThunder->SetPos(vecMon[monIdx]->GetLocalPos());

	//for (size_t i = 0; i < vecMon.size(); ++i)
	//{
	//	monsterPos = vecMon[i]->GetLocalPos();
	//	if (length > (playerPos - monsterPos).Length())	// �÷��̾�� ������ ���̰� length ���� ���� �� (���� ����� �� ã��)
	//	{
	//		length = (playerPos - monsterPos).Length(); // length �� �� ����
	//		pThunder->SetPos(monsterPos);
	//	}
	//}

	CreateObject(pThunder, GROUP_TYPE::PROJ_PLAYER);

	if (mThunderSound)
		mThunderSound->Play();

	SetSkillTime(0.f);
}

void Thunder::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}