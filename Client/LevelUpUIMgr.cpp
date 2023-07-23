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
#include "TextUI.h"


SINGLE_HEADER(LevelUpUIMgr);


LevelUpUIMgr::LevelUpUIMgr()
	: mMapLvupEffectData{}
	, mCurLvupUI{}
{
}

LevelUpUIMgr::~LevelUpUIMgr()
{
	for (size_t i = 0; i < mCurLvupUI.size(); ++i)
	{
		if (nullptr != mCurLvupUI[i])
			DeleteObject(mCurLvupUI[i]);
	}

	mMapLvupEffectData.clear();
}


void LevelUpUIMgr::Init()
{
	mMapLvupEffectData[STATEUP_TYPE::FULL_HP_UP]			= { L"최대 체력 증가", L"강인함" };
	mMapLvupEffectData[STATEUP_TYPE::REGENERATION_HP_UP]	= { L"체력 재생 증가", L"생명력" };
	mMapLvupEffectData[STATEUP_TYPE::MOVE_SPEED_UP]			= { L"이동속도 증가", L"순발력" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_DAMAGE_UP]			= { L"공격력 증가", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_SPEED_UP]			= { L"공격속도 증가", L"신속" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_RANGE_UP]			= { L"사거리 증가", L"판단력" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_SPEED_UP]			= { L"탄속 증가", L"절대집중" };
	mMapLvupEffectData[STATEUP_TYPE::RELOAD_SPEED_UP]		= { L"재장전 속도 증가", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_ANGLE_UP]			= { L"명중률 증가", L"집중" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_COUNT_UP]			= { L"발사되는 총알 개수 증가", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::PENETRATION_UP]		= { L"총알이 적을 관통하는 횟수 증가", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::SPLITCOUNT_UP]			= { L"분열되는 총알의 개수 증가", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::BOUNTCECOUNT_UP]		= { L"총알이 벽에 튕기는 횟수 증가", L"__Test__" };

	mMapLvupEffectData_Skill[SKILL_TYPE::ICE_BOLT]		= { L"테스트 스킬 1 업그레이드", L"아이스볼트" };
	mMapLvupEffectData_Skill[SKILL_TYPE::ENERGY_BALL]	= { L"테스트 스킬 1 업그레이드", L"에너지볼" };
	mMapLvupEffectData_Skill[SKILL_TYPE::THUNDER]		= { L"테스트 스킬 2 업그레이드", L"번개" };
	mMapLvupEffectData_Skill[SKILL_TYPE::CIRCLING_BALL] = { L"테스트 스킬 3 업그레이드", L"서클링볼" };

	Vect2 vRes = CCore::GetI()->GetResolution();

	CImageUI* pImg = new CImageUI;
	pImg->SetScale(vRes);
	pImg->SetPos(vRes * 0.5f);
	pImg->SetColor(RGB(0, 0, 0));
	pImg->SetAlpha(128.f);
	mLevelUpUIPanel = pImg;

	CImageUI* pMainPanelImg = new CImageUI;
	pMainPanelImg->SetScale(Vect2(vRes.x * 0.9f, vRes.y * 0.55f));
	pMainPanelImg->SetPos(Vect2::zero);
	pMainPanelImg->SetColor(RGB(0, 0, 0));
	pMainPanelImg->SetAlpha(128.f);
	mLevelUpUIPanel->AddChild(pMainPanelImg);

	TextUI* pText = new TextUI;
	pText->SetPos(Vect2(0, -280));
	pText->SetFontSize(80.f);
	pText->SetColor(RGB(255, 255, 255));
	pText->SetOutlineWidth(3.f);
	pText->SetOutlineColor(RGB(0, 0, 0));
	pText->SetText(L"Level Up");
	mLevelUpUIPanel->AddChild(pText);

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


void LevelUpUIMgr::Choice()
{
	tLeveUpEvent tEventArr[3];

	for (int i = 0; i < 3; ++i)
	{
		tEventArr[i].type = (LEVELUP_TYPE)CRandom::GetI()->Next(0, (int)LEVELUP_TYPE::ITEM);

		switch (tEventArr[i].type)
		{
		case LEVELUP_TYPE::STATE:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)STATEUP_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData[(STATEUP_TYPE)tEventArr[i].lParam];
		}
		break;
		case LEVELUP_TYPE::SKILL:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)SKILL_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData_Skill[(SKILL_TYPE)tEventArr[i].lParam];
		}
		break;
		case LEVELUP_TYPE::ITEM:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)SKILL_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData_Skill[(SKILL_TYPE)tEventArr[i].lParam];
		}
		break;
		}

		for (int j = 0; j < i; ++j)
		{
			if (tEventArr[j] == tEventArr[i])
				--i;
		}
	}

	for (int i = 0; i < mCurLvupUI.size(); ++i)
	{
		mCurLvupUI[i]->SetEffect(tEventArr[i]);
	}

	mLevelUpUIPanel->SetVisible(true);
	CUIMgr::GetI()->SetTop(mLevelUpUIPanel);
	CTimeMgr::GetI()->Stop();
}


void LevelUpUIMgr::Delete()
{
	mLevelUpUIPanel->SetVisible(false);
}