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
	mThunderSound->SetVolumeOffset(200);
}

Thunder::~Thunder()
{
}

void Thunder::UseSkill()
{
	CScene* cscene = CSceneMgr::GetI()->GetCurScene();
	const vector<CObject*>& vecMon = cscene->GetGroupObject(GROUP_TYPE::MONSTER);
	const vector<CObject*>& vecBoss = cscene->GetGroupObject(GROUP_TYPE::BOSS);

	if (vecMon.size() > 0)
	{
		SkillObj* pThunder = new Thunder_Obj;
		pThunder->SetOwner(this);

		int monIdx = CRandom::GetI()->Next(0, vecMon.size());
		pThunder->SetPos(vecMon[monIdx]->GetLocalPos());
		CreateObject(pThunder, GROUP_TYPE::PROJ_PLAYER);

		if (mThunderSound)
		{
			mThunderSound->Play();
		}
	}
	else if (vecBoss.size() > 0)
	{
		SkillObj* pThunder = new Thunder_Obj;
		pThunder->SetOwner(this);

		pThunder->SetPos(vecBoss[0]->GetLocalPos());
		CreateObject(pThunder, GROUP_TYPE::PROJ_PLAYER);

		if (mThunderSound)	mThunderSound->Play();
	}

	SetSkillTime(0.8f * GetSkillLevel() / 5);
}

void Thunder::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}