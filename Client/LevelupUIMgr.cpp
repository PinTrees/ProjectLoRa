#include "pch.h"
#include "LevelUpUIMgr.h"
#include "LevelUpUI.h"
#include "Random.h"
#include "Player.h"
#include "CTimeMgr.h"

#include "UIMgr.h"


SINGLE_HEADER(LevelupUIMgr);


LevelupUIMgr::LevelupUIMgr()
	: mMapLvUpEffectData{}
	, mCurLvupUI{}
{
}

LevelupUIMgr::~LevelupUIMgr()
{
	for (size_t i = 0; i < mCurLvupUI.size(); ++i)
	{
		if (nullptr != mCurLvupUI[i])
			DeleteObject(mCurLvupUI[i]);
	}

	mMapLvUpEffectData.clear();
}


void LevelupUIMgr::Init()
{
	mMapLvUpEffectData[LEVELUP_EFFECT::FULL_HP_UP]			= { L"최대 체력 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::REGENERATION_HP_UP]	= { L"체력 재생 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::MOVE_SPEED_UP]		= { L"이동속도 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_DAMAGE_UP]		= { L"공격력 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_SPEED_UP]		= { L"공격속도 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_RANGE_UP]		= { L"사거리 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_SPEED_UP]		= { L"탄속 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::RELOAD_SPEED_UP]		= { L"재장전 속도 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_ANGLE_UP]		= { L"명중률 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_COUNT_UP]		= { L"발사되는 총알 개수 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::PENETRATION_UP]		= { L"총알이 적을 관통하는 횟수 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SPLITCOUNT_UP]		= { L"분열되는 총알의 개수 증가", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::BOUNTCECOUNT_UP]		= { L"총알이 벽에 튕기는 횟수 증가", L"" };

	for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		mCurLvupUI[i] = new LevelupUI;
		mCurLvupUI[i]->SetVisible(false);
		mCurLvupUI[i]->SetPos(Vect2(230.f + (float)i * 400.f, 350.f));
		CreateObject(mCurLvupUI[i], GROUP_TYPE::UI);
	}
}


void LevelupUIMgr::Choice()
{
	int a = 0;
	int rand[3];
	for (int i = 0; i < 3; ++i)
	{
		rand[i] = CRandom::GetI()->Next(0, (int)LEVELUP_EFFECT::END);
		for (int j = 0; j < i; ++j)
		{
			if (rand[j] == rand[i])
				--i;
		}
	}

	for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		CUIMgr::GetI()->SetFocusUI(mCurLvupUI[i]);
		mCurLvupUI[i]->SetVisible(true);
		mCurLvupUI[i]->SetTitle(mMapLvUpEffectData[(LEVELUP_EFFECT)rand[i]].titleStr);
	}

	CTimeMgr::GetI()->Stop();
}


void LevelupUIMgr::Delete()
{
	for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		mCurLvupUI[i]->SetVisible(false);
	}
}