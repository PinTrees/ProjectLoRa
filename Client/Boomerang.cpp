#include "pch.h"
#include "Boomerang.h"
#include "Boomerang_Obj.h"

#include "PlayerMgr.h"
#include "CSceneMgr.h"

#include "Player.h"
#include "CScene.h"

#include "CSound.h"
#include "Random.h"
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

	Vect2 vDir = Vect2(CRandom::GetI()->Next(-50, 50), CRandom::GetI()->Next(-50, 50)).Normalize();

	Boomerang_Obj* boomerang = new Boomerang_Obj;
	boomerang->SetDir(vDir);
	boomerang->SetOwner(this);
	boomerang->SetPos(vPlayerPos);

	CreateObject(boomerang, GROUP_TYPE::PROJ_PLAYER);

	if (mpSound)
		mpSound->Play();

	SetSkillTime(0.f);
}

void Boomerang::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown())
	{
		SetAvailable(true);
	}
}