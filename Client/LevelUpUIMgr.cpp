#include "pch.h"
#include "LevelUpUIMgr.h"
#include "LevelUpUI.h"
#include "Random.h"
#include "Player.h"
#include "CTimeMgr.h"

#include "CCore.h"
#include "UIMgr.h"
#include "CRow.h"
#include "CImageUI.h"


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
	mMapLvUpEffectData[LEVELUP_EFFECT::FULL_HP_UP]			= { L"�ִ� ü�� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::REGENERATION_HP_UP]	= { L"ü�� ��� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::MOVE_SPEED_UP]		= { L"�̵��ӵ� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_DAMAGE_UP]		= { L"���ݷ� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_SPEED_UP]		= { L"���ݼӵ� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::ATK_RANGE_UP]		= { L"��Ÿ� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_SPEED_UP]		= { L"ź�� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::RELOAD_SPEED_UP]		= { L"������ �ӵ� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_ANGLE_UP]		= { L"���߷� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SHOT_COUNT_UP]		= { L"�߻�Ǵ� �Ѿ� ���� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::PENETRATION_UP]		= { L"�Ѿ��� ���� �����ϴ� Ƚ�� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::SPLITCOUNT_UP]		= { L"�п��Ǵ� �Ѿ��� ���� ����", L"" };
	mMapLvUpEffectData[LEVELUP_EFFECT::BOUNTCECOUNT_UP]		= { L"�Ѿ��� ���� ƨ��� Ƚ�� ����", L"" };

	Vect2 vRes = CCore::GetI()->GetResolution();

	CImageUI* pImg = new CImageUI;
	pImg->SetScale(vRes);
	pImg->SetPos(vRes * 0.5f);
	pImg->SetColor(RGB(0, 0, 0));
	pImg->SetAlpha(180.f);
	mLevelUpUIPanel = pImg;

	CRow* pRowUI = new CRow;
	pRowUI->SetPos(Vect2::zero);
	pRowUI->SetScale(vRes);
	pRowUI->SetSpacing(48.f);
    pImg->AddChild(pRowUI);

	for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		mCurLvupUI[i] = new LevelupUI;
		mCurLvupUI[i]->SetPos(Vect2(230.f + (float)i * 400.f, 350.f));
		pRowUI->AddChild(mCurLvupUI[i]);
	}

	CreateObject(mLevelUpUIPanel, GROUP_TYPE::UI);
	mLevelUpUIPanel->SetVisible(false);
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
		mCurLvupUI[i]->SetTitle(mMapLvUpEffectData[(LEVELUP_EFFECT)rand[i]].titleStr);
	}

	mLevelUpUIPanel->SetVisible(true);
	CUIMgr::GetI()->SetFocusUI(mLevelUpUIPanel);
	CTimeMgr::GetI()->Stop();
}


void LevelupUIMgr::Delete()
{
	mLevelUpUIPanel->SetVisible(false);
	/*for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		mCurLvupUI[i]->SetVisible(false);
	}*/
}