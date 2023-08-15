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
	, mCurLvupUI3{}
	, mCurLvupUI2{}
	, mCurLvupUI1{}
	, mLevelUpUIPanel3(nullptr)
	, mLevelUpUIPanel2(nullptr)
	, mLevelUpUIPanel1(nullptr)
{
}

LevelUpUIMgr::~LevelUpUIMgr()
{
	for (size_t i = 0; i < mCurLvupUI3.size(); ++i)
	{
		if (nullptr != mCurLvupUI3[i])
			DeleteObject(mCurLvupUI3[i]);
	}
	for (size_t i = 0; i < mCurLvupUI2.size(); ++i)
	{
		if (nullptr != mCurLvupUI2[i])
			DeleteObject(mCurLvupUI2[i]);
	}

	if (nullptr != mCurLvupUI1)
		DeleteObject(mCurLvupUI1);

	mMapLvupEffectData.clear();
	mMapLvupEffectData_Skill.clear();
}


void LevelUpUIMgr::Init()
{
	mMapLvupEffectData[STATEUP_TYPE::FULL_HP_UP] = { L"최대 체력 증가", L"강인함", L"hp_max.bmp" };
	mMapLvupEffectData[STATEUP_TYPE::REGENERATION_HP_UP] = { L"체력 재생 증가", L"생명력", L"hp.bmp" };
	//mMapLvupEffectData[STATEUP_TYPE::MOVE_SPEED_UP] = { L"이동속도 증가", L"순발력", L"speed.bmp" };
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

	CImageUI* pMainPanelImg = new CImageUI;
	pMainPanelImg->SetScale(Vect2(vRes.x * 0.9f, vRes.y * 0.55f));
	pMainPanelImg->SetPos(Vect2::zero);
	pMainPanelImg->SetColor(RGB(0, 0, 0));
	pMainPanelImg->SetAlpha(128.f);
	//mLevelUpUIPanel->AddChild(pMainPanelImg);

	///////// 레벨업 UI 3개 세팅 //////////
	CImageUI* pImg3 = new CImageUI;
	pImg3->SetScale(vRes);
	pImg3->SetPos(vRes * 0.5f);
	pImg3->SetColor(RGB(0, 0, 0));
	pImg3->SetAlpha(150.f);
	mLevelUpUIPanel3 = pImg3;

	TextUI* pText3 = new TextUI;
	pText3->SetPos(Vect2(0, -280));
	pText3->SetFontSize(80.f);
	pText3->SetColor(RGB(255, 255, 255));
	pText3->SetOutlineWidth(3.f);
	pText3->SetOutlineColor(RGB(0, 0, 0));
	pText3->SetText(L"Level Up");
	mLevelUpUIPanel3->AddChild(pText3);

	CRow* pRowUI3 = new CRow;
	pRowUI3->SetPos(Vect2::zero);
	pRowUI3->SetScale(vRes);
	pRowUI3->SetSpacing(48.f);
	pImg3->AddChild(pRowUI3);

	for (int i = 0; i < mCurLvupUI3.size(); ++i)
	{
		mCurLvupUI3[i] = new LevelupUI;
		mCurLvupUI3[i]->SetPos(Vect2(230.f + (float)i * 400.f, 350.f));
		pRowUI3->AddChild(mCurLvupUI3[i]);
	}
	CreateObject(mLevelUpUIPanel3, GROUP_TYPE::UI);
	mLevelUpUIPanel3->SetVisible(false);
	/////////////////////////////////////

	///////// 레벨업 UI 2개 세팅 //////////
	CImageUI* pImg2 = new CImageUI();
	pImg2->SetScale(vRes);
	pImg2->SetPos(vRes * 0.5f);
	pImg2->SetColor(RGB(0, 0, 0));
	pImg2->SetAlpha(150.f);
	mLevelUpUIPanel2 = pImg2;

	TextUI* pText2 = new TextUI;
	pText2->SetPos(Vect2(0, -280));
	pText2->SetFontSize(80.f);
	pText2->SetColor(RGB(255, 255, 255));
	pText2->SetOutlineWidth(3.f);
	pText2->SetOutlineColor(RGB(0, 0, 0));
	pText2->SetText(L"Level Up");
	mLevelUpUIPanel3->AddChild(pText2);

	CRow* pRowUI2 = new CRow;
	pRowUI2->SetPos(Vect2::zero);
	pRowUI2->SetScale(vRes);
	pRowUI2->SetSpacing(48.f);
	pImg2->AddChild(pRowUI2);

	for (int i = 0; i < mCurLvupUI2.size(); ++i)
	{
		mCurLvupUI2[i] = new LevelupUI;
		mCurLvupUI2[i]->SetPos(Vect2(230.f + (float)i * 400.f, 350.f));
		pRowUI2->AddChild(mCurLvupUI2[i]);
	}
	CreateObject(mLevelUpUIPanel2, GROUP_TYPE::UI);
	mLevelUpUIPanel2->SetVisible(false);
	/////////////////////////////////////

	///////// 레벨업 UI 1개 세팅 //////////
	CImageUI* pImg1 = new CImageUI;
	pImg1->SetScale(vRes);
	pImg1->SetPos(vRes * 0.5f);
	pImg1->SetColor(RGB(0, 0, 0));
	pImg1->SetAlpha(150.f);
	mLevelUpUIPanel1 = pImg1;

	TextUI* pText1 = new TextUI;
	pText1->SetPos(Vect2(0, -280));
	pText1->SetFontSize(80.f);
	pText1->SetColor(RGB(255, 255, 255));
	pText1->SetOutlineWidth(3.f);
	pText1->SetOutlineColor(RGB(0, 0, 0));
	pText1->SetText(L"Level Up");
	mLevelUpUIPanel3->AddChild(pText1);

	CRow* pRowUI1 = new CRow;
	pRowUI1->SetPos(Vect2::zero);
	pRowUI1->SetScale(vRes);
	pRowUI1->SetSpacing(48.f);
	pImg1->AddChild(pRowUI1);

	mCurLvupUI1 = new LevelupUI;
	mCurLvupUI1->SetPos(Vect2(230.f + (float)0 * 400.f, 350.f));
	pRowUI1->AddChild(mCurLvupUI1);
	CreateObject(mLevelUpUIPanel1, GROUP_TYPE::UI);
	mLevelUpUIPanel1->SetVisible(false);
	/////////////////////////////////////
}


void LevelUpUIMgr::Choice()
{
	Player* player = PlayerMgr::GetI()->GetPlayer();

	const vector<STATEUP_TYPE>& vecMaxState = player->GetMaxLevelStatus();
	const vector<SKILL_TYPE>& vecMaxSkill = player->GetMaxLevelSkill();

	if (vecMaxState.size() == (size_t)STATEUP_TYPE::END			// 모든 스탯과 스킬이 maxlevel 일 경우 함수를 탈출
		&& vecMaxSkill.size() == (size_t)SKILL_TYPE::END)
		return;

	int count = 3;

	if ((int)(((size_t)STATEUP_TYPE::END - vecMaxState.size()) + ((size_t)SKILL_TYPE::END - vecMaxSkill.size())) < 3)
	{
		count = (int)(((size_t)STATEUP_TYPE::END - vecMaxState.size()) + ((size_t)SKILL_TYPE::END - vecMaxSkill.size()));
	}

	tLeveUpEvent* tEventArr = new tLeveUpEvent[count];
	bool ReChoice = false;

	for (int i = 0; i < count; ++i)
	{
		tEventArr[i].type = (LEVELUP_TYPE)CRandom::GetI()->Next(0, (int)LEVELUP_TYPE::END);

		switch (tEventArr[i].type)
		{
		case LEVELUP_TYPE::STATE:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)STATEUP_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData[(STATEUP_TYPE)tEventArr[i].lParam];

			for (size_t s = 0; s < vecMaxState.size(); ++s)
			{
				if ((STATEUP_TYPE)tEventArr[i].lParam == vecMaxState[s])
				{
					ReChoice = true;
					break;
				}
			}
		}
		break;
		case LEVELUP_TYPE::SKILL:
		{
			tEventArr[i].lParam = CRandom::GetI()->Next(0, (int)SKILL_TYPE::END);
			tEventArr[i].wParam = (DWORD_PTR)&mMapLvupEffectData_Skill[(SKILL_TYPE)tEventArr[i].lParam];

			// 뽑은 스킬이 만렙상태의 스킬타입과 일치하면 다시 뽑도록 함
			for (size_t s = 0; s < vecMaxSkill.size(); ++s)
			{
				if ((SKILL_TYPE)tEventArr[i].lParam == vecMaxSkill[s])
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

			// 뽑은 스킬이 만렙상태의 스킬타입과 일치하면 다시 뽑도록 함
			for (size_t s = 0; s < vecMaxSkill.size(); ++s)
			{
				if ((SKILL_TYPE)tEventArr[i].lParam == vecMaxSkill[s])
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

	switch (count)
	{
	case 3:
		for (int i = 0; i < mCurLvupUI3.size(); ++i)
		{
			mCurLvupUI3[i]->SetEffect(tEventArr[i]);
			mLevelUpUIPanel3->SetVisible(true);
			CUIMgr::GetI()->SetTop(mLevelUpUIPanel3);
		}
		break;

	case 2:
		for (int i = 0; i < mCurLvupUI2.size(); ++i)
		{
			mCurLvupUI2[i]->SetEffect(tEventArr[i]);
			mLevelUpUIPanel2->SetVisible(true);
			CUIMgr::GetI()->SetTop(mLevelUpUIPanel2);
		}
		break;

	case 1:
		mCurLvupUI1->SetEffect(tEventArr[0]);
		mLevelUpUIPanel1->SetVisible(true);
		CUIMgr::GetI()->SetTop(mLevelUpUIPanel1);
		break;
	}
	delete[] tEventArr;
	CTimeMgr::GetI()->Stop();
}


void LevelUpUIMgr::Delete()
{
	mLevelUpUIPanel3->SetVisible(false);
	mLevelUpUIPanel2->SetVisible(false);
	mLevelUpUIPanel1->SetVisible(false);
}

