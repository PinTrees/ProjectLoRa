#include "pch.h"
#include "CrossDagger.h"
#include "CrossDagger_Obj.h"

#include "Player.h"
#include "PlayerMgr.h"

#include "CSound.h"
#include "CResMgr.h"



CrossDagger::CrossDagger()
	: Skill(SKILL_TYPE::CROSS_DAGGER, 8)
	, mCount(4)
{
	SetIconStr(L"7.bmp");
	SetCoolDown(3.f);

	mpSound = CResMgr::GetI()->LoadSound(L"Skill_7", L"sound\\skill\\7.wav");
	mpSound->SetVolumeOffset(-300);
}

CrossDagger::~CrossDagger()
{
}


void CrossDagger::UseSkill()
{
	float Theta;
	int count = mCount + GetSkillLevel() - 1;
	Theta = 2 * PI / count;

	for (int i = 0; i < count; ++i)		// 정해진 개수만큼 표창 생성
	{
		CrossDagger_Obj* pDagger = new CrossDagger_Obj;
		pDagger->SetOwner(this);
		pDagger->SetPos(PlayerMgr::GetI()->GetPlayer()->GetPos());
		pDagger->SetTheta(Theta * i);		// 표창의 간격이 일정하도록 계산

		CreateObject(pDagger, GROUP_TYPE::PROJ_PLAYER);
	}

	if (mpSound)
		mpSound->Play();

	SetSkillTime(0.f);
}

void CrossDagger::CheckAvailable()
{
	if (GetSkillTime() >= GetCoolDown()) // 쿨타임이 끝나면 다시 사용가능 상태로 세팅
	{
		SetAvailable(true);
	}
}

void CrossDagger::AddSkillLevel()
{
	Skill::AddSkillLevel();

	float newCoolDown = GetCoolDown() - 0.2f * GetSkillLevel();
	SetCoolDown(newCoolDown);
}
