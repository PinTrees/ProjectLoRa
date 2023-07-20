#include "pch.h"
#include "LevelUpUI.h"

#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CResMgr.h"
#include "TextUI.h"
#include "Player.h"
#include "CTimeMgr.h"
#include "UIMgr.h"
#include "LevelUpUIMgr.h"
#include "CFont.h"

// Game Manager Header
#include "PlayerMgr.h"
#include "SkillMgr.h"

#include "Skill.h"
#include "Random.h"



LevelupUI::LevelupUI()
	: CPanelUI()
	, mInfo({})
	, mInfoText(nullptr)
	, mSelectBtn(nullptr)
{
	// ���ο� UI Ʋ�� �����ؾ��� ��� �ش���� �ڽ� UI ������ ũ�� ������ ���� ��� ���� ������ �Ҵ�� �ڽ����� �߰�
	SetPos(Vect2::zero);
	SetScale(Vect2(300.f, 300.f));
	SetTexture(CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));

	mTitleText = new TextUI;
	mTitleText->SetPos(Vect2(0.f, -120.f));
	mTitleText->SetScale(Vect2(0.f, 50.f));
	mTitleText->SetText(L"");
	mTitleText->SetOutlineColor(RGB(255, 255, 255));
	mTitleText->SetOutlineWidth(2);
	mTitleText->SetColor(RGB(0, 0, 0));
	mTitleText->SetFontSize(32);
	this->AddChild(mTitleText);

	mInfoText = new TextUI;
	mInfoText->SetPos(Vect2(0.f, 0.f));
	mInfoText->SetScale(Vect2(260.f, 50.f));
	mInfoText->SetText(L"");
	mInfoText->SetColor(RGB(255, 255, 255));
	mInfoText->SetFontSize(24);
	this->AddChild(mInfoText);

	mSelectBtn = new CBtnUI;
	mSelectBtn->SetPos(Vect2(0.f, 100.f));
	mSelectBtn->SetScale(Vect2(200.f, 50.f));
	mSelectBtn->SetText(L"����");
	mSelectBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	mSelectBtn->SetClickedCallBack(this, (OBJECT_FUNC)&LevelupUI::ApplyLevelUp);
	this->AddChild(mSelectBtn);
}

LevelupUI::~LevelupUI()
{
}


void LevelupUI::SetEffect(tLeveUpEvent event)
{
	mInfo = event;

	tLvupEffectData* tEventData = (tLvupEffectData*)event.wParam;
	mTitleText->SetText(tEventData->titleStr);
	mInfoText->SetText(tEventData->infoStr);
}



void LevelupUI::ApplyLevelUp()
{

	switch (mInfo.type)
	{
	case LEVELUP_TYPE::STATE:
	{
		statusUp((STATEUP_TYPE)mInfo.lParam);
	}
	break;
	case LEVELUP_TYPE::SKILL:
	{
		skillUp((SKILL_TYPE)mInfo.lParam);
	}
	break;
	case LEVELUP_TYPE::ITEM:
	{
	}
	break;
	}

	CTimeMgr::GetI()->Play();
	CUIMgr::GetI()->SetFocusUI(nullptr);
	LevelUpUIMgr::GetI()->Delete();
}




void LevelupUI::statusUp(STATEUP_TYPE state)
{
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();

	switch (state)
	{
	case STATEUP_TYPE::FULL_HP_UP:					// �ִ� ü�� ����
		pPlayer->mtInfo.fullHP += 10.f;
		break;
	case STATEUP_TYPE::REGENERATION_HP_UP:			// ü�� ��� ����
		pPlayer->mtInfo.regenerationHP += 10.f;
		break;
	case STATEUP_TYPE::MOVE_SPEED_UP:					// �̵��ӵ� ����
		pPlayer->mtInfo.moveSpeed += 20.f;
		break;
	case STATEUP_TYPE::ATK_DAMAGE_UP:					// ���ݷ� ����
		pPlayer->mtInfo.atkDamage += 15.f;
		break;
	case STATEUP_TYPE::ATK_SPEED_UP:					// ���ݼӵ� ����
		pPlayer->mtInfo.atkSpeed += 10.f;
		break;
	case STATEUP_TYPE::ATK_RANGE_UP:					// ��Ÿ� ����
		pPlayer->mtInfo.atkRange += 100.f;
		break;
	case STATEUP_TYPE::SHOT_SPEED_UP:					// ź�� ����
		pPlayer->mtInfo.shotSpeed += 50.f;
		break;
	case STATEUP_TYPE::RELOAD_SPEED_UP:				// �����ӵ� ����
		pPlayer->mtInfo.reloadSpeed += 20.f;
		break;
	case STATEUP_TYPE::SHOT_ANGLE_UP:					// ���߷� ����
		pPlayer->mtInfo.shotAngle += 10.f;
		break;
	case STATEUP_TYPE::SHOT_COUNT_UP:					// �߻�Ǵ� ź�� �� ����
		pPlayer->mtInfo.shotCount += 2.f;
		break;
	case STATEUP_TYPE::PENETRATION_UP:				// ���� �����ϴ� Ƚ�� ����
		pPlayer->mtInfo.penetration += 1;
		break;
	case STATEUP_TYPE::SPLITCOUNT_UP:					// �п��Ǵ� �Ѿ� ���� ����
		pPlayer->mtInfo.splitCount += 1;
		break;
	case STATEUP_TYPE::BOUNTCECOUNT_UP:				// ���� ƨ��� Ƚ�� ����
		pPlayer->mtInfo.bounceCount += 1;
		break;
	}
}

void LevelupUI::skillUp(SKILL_TYPE state)
{
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
	Skill* pSkill = pPlayer->FindSkill(state);

	if (nullptr == pSkill)
	{
		pSkill = SkillMgr::GetI()->GetSkill(state);
	}
	else
	{
		pSkill->AddSkillLevel();
	}
}