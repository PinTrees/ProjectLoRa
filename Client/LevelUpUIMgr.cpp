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
	mMapLvupEffectData[STATEUP_TYPE::FULL_HP_UP]			= { L"�ִ� ü�� ����", L"������" };
	mMapLvupEffectData[STATEUP_TYPE::REGENERATION_HP_UP]	= { L"ü�� ��� ����", L"�����" };
	mMapLvupEffectData[STATEUP_TYPE::MOVE_SPEED_UP]			= { L"�̵��ӵ� ����", L"���߷�" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_DAMAGE_UP]			= { L"���ݷ� ����", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_SPEED_UP]			= { L"���ݼӵ� ����", L"�ż�" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_RANGE_UP]			= { L"��Ÿ� ����", L"�Ǵܷ�" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_SPEED_UP]			= { L"ź�� ����", L"��������" };
	mMapLvupEffectData[STATEUP_TYPE::RELOAD_SPEED_UP]		= { L"������ �ӵ� ����", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_ANGLE_UP]			= { L"���߷� ����", L"����" };
	mMapLvupEffectData[STATEUP_TYPE::SHOT_COUNT_UP]			= { L"�߻�Ǵ� �Ѿ� ���� ����", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::PENETRATION_UP]		= { L"�Ѿ��� ���� �����ϴ� Ƚ�� ����", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::SPLITCOUNT_UP]			= { L"�п��Ǵ� �Ѿ��� ���� ����", L"__Test__" };
	mMapLvupEffectData[STATEUP_TYPE::BOUNTCECOUNT_UP]		= { L"�Ѿ��� ���� ƨ��� Ƚ�� ����", L"__Test__" };

	mMapLvupEffectData_Skill[SKILL_TYPE::ICE_BOLT]		= { L"�׽�Ʈ ��ų 1 ���׷��̵�", L"���̽���Ʈ" };
	mMapLvupEffectData_Skill[SKILL_TYPE::ENERGY_BALL]	= { L"�׽�Ʈ ��ų 1 ���׷��̵�", L"��������" };
	mMapLvupEffectData_Skill[SKILL_TYPE::THUNDER]		= { L"�׽�Ʈ ��ų 2 ���׷��̵�", L"����" };
	mMapLvupEffectData_Skill[SKILL_TYPE::CIRCLING_BALL] = { L"�׽�Ʈ ��ų 3 ���׷��̵�", L"��Ŭ����" };

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