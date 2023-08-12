#include "pch.h"
#include "LevelUpUIMgr.h"
#include "LevelUpUI.h"
#include "Random.h"
#include "Player.h"
#include "CTimeMgr.h"

#include "PlayerMgr.h"

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
	mMapLvupEffectData_Skill.clear();
}


void LevelUpUIMgr::Init()
{
	mMapLvupEffectData[STATEUP_TYPE::FULL_HP_UP] = { L"최대 체력 증가", L"강인함", L"hp_max.bmp" };
	mMapLvupEffectData[STATEUP_TYPE::REGENERATION_HP_UP] = { L"체력 재생 증가", L"생명력", L"hp.bmp" };
	mMapLvupEffectData[STATEUP_TYPE::MOVE_SPEED_UP] = { L"이동속도 증가", L"순발력", L"speed.bmp" };
	mMapLvupEffectData[STATEUP_TYPE::ATK_DAMAGE_UP] = { L"공격력 증가", L"주문력", L"atk.bmp" };
	//mMapLvupEffectData[STATEUP_TYPE::ATK_SPEED_UP]			= { L"공격속도 증가", L"신속" };
	//mMapLvupEffectData[STATEUP_TYPE::ATK_RANGE_UP]			= { L"사거리 증가", L"판단력" };
	//mMapLvupEffectData[STATEUP_TYPE::SHOT_SPEED_UP]			= { L"탄속 증가", L"절대집중" };
	//mMapLvupEffectData[STATEUP_TYPE::RELOAD_SPEED_UP]		= { L"재장전 속도 증가", L"__Test__" };
	//mMapLvupEffectData[STATEUP_TYPE::SHOT_ANGLE_UP]			= { L"명중률 증가", L"집중" };
	//mMapLvupEffectData[STATEUP_TYPE::SHOT_COUNT_UP]			= { L"발사되는 총알 개수 증가", L"__Test__" };
	//mMapLvupEffectData[STATEUP_TYPE::PENETRATION_UP]		= { L"총알이 적을 관통하는 횟수 증가", L"__Test__" };
	//mMapLvupEffectData[STATEUP_TYPE::SPLITCOUNT_UP]			= { L"분열되는 총알의 개수 증가", L"__Test__" };
	//mMapLvupEffectData[STATEUP_TYPE::BOUNTCECOUNT_UP]		= { L"총알이 벽에 튕기는 횟수 증가", L"__Test__" };

	mMapLvupEffectData_Skill[SKILL_TYPE::ICE_BOLT] = { L"적에게 얼음 창을 발사합니다.", L"아이스볼트", L"2.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::ENERGY_BALL] = { L"적에게 에너지 구체를 발사합니다.", L"에너지볼", L"4.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::THUNDER] = { L"무작위 적 번개 공격", L"번개", L"2.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::CIRCLING_BALL] = { L"플레이어 주위를 맴도는 공", L"서클링볼", L"3.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::HOLYAREA] = { L"플레이어 주위에 가까운 적을 공격", L"성역", L"5.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::GRENADE] = { L"적에게 수류탄을 투척합니다.", L"수류탄", L"6.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::CROSS_DAGGER] = { L"표창 발사 공격", L"표창", L"7.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::BOOMERANG] = { L"부메랑 발사 공격", L"부메랑", L"8.bmp" };
	mMapLvupEffectData_Skill[SKILL_TYPE::COMBAT_BALL] = { L"테스트 스킬 8 업그레이드", L"전투오브", L"9.bmp" };

	Vect2 vRes = CCore::GetI()->GetResolution();

	CImageUI* pImg = new CImageUI;
	pImg->SetScale(vRes);
	pImg->SetPos(vRes * 0.5f);
	pImg->SetColor(RGB(0, 0, 0));
	pImg->SetAlpha(150.f);
	mLevelUpUIPanel = pImg;

	CImageUI* pMainPanelImg = new CImageUI;
	pMainPanelImg->SetScale(Vect2(vRes.x * 0.9f, vRes.y * 0.55f));
	pMainPanelImg->SetPos(Vect2::zero);
	pMainPanelImg->SetColor(RGB(0, 0, 0));
	pMainPanelImg->SetAlpha(128.f);
	//mLevelUpUIPanel->AddChild(pMainPanelImg);

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
	bool ReChoice = false;

	for (int i = 0; i < 3; ++i)
	{
		tEventArr[i].type = (LEVELUP_TYPE)CRandom::GetI()->Next(0, (int)LEVELUP_TYPE::END);

		switch (tEventArr[i].type)
		{
		case LEVELUP_TYPE::STATE:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)STATEUP_TYPE::ATK_SPEED_UP);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData[(STATEUP_TYPE)tEventArr[i].lParam];
		}
		break;
		case LEVELUP_TYPE::SKILL:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)SKILL_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData_Skill[(SKILL_TYPE)tEventArr[i].lParam];

			Player* player = PlayerMgr::GetI()->GetPlayer();		// 뽑은 스킬이 만렙상태의 스킬타입과 일치하면 다시 뽑도록 함
			const vector<SKILL_TYPE>& vecMax = player->GetMaxLevelSkill();

			for (size_t s = 0; s < vecMax.size(); ++s)
			{
				if ((SKILL_TYPE)tEventArr[i].lParam == vecMax[s])
				{
					ReChoice = true;
					break;
				}
			}
		}
		break;
		case LEVELUP_TYPE::ITEM:
		{
			// 스킬 확률 증가
			tEventArr[i].type = (LEVELUP_TYPE)LEVELUP_TYPE::SKILL;
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)SKILL_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData_Skill[(SKILL_TYPE)tEventArr[i].lParam];

			Player* player = PlayerMgr::GetI()->GetPlayer();		// 뽑은 스킬이 만렙상태의 스킬타입과 일치하면 다시 뽑도록 함
			vector<SKILL_TYPE> vecMax = player->GetMaxLevelSkill();

			for (size_t s = 0; s < vecMax.size(); ++s)
			{
				if ((SKILL_TYPE)tEventArr[i].lParam == vecMax[s])
				{
					ReChoice = true;
					break;
				}
			}
		}
		break;
		}

		if (ReChoice)
		{
			--i;
			ReChoice = false;
			continue;
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