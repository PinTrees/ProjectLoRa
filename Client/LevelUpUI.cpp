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


LevelupUI::LevelupUI()
	: CPanelUI()
	, mEffect()
	, mTitleText(nullptr)
	, mSelectBtn(nullptr)
{
	// ���ο� UI Ʋ�� �����ؾ��� ��� �ش���� �ڽ� UI ������ ũ�� ������ ���� ��� ���� ������ �Ҵ�� �ڽ����� �߰�
	SetPos(Vect2::zero);
	SetScale(Vect2(300.f, 300.f));
	SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Panel_1", L"texture\\ui\\panel_1.bmp"));

	mTitleText = new TextUI;
	mTitleText->SetPos(Vect2(0.f, 0.f));
	mTitleText->SetScale(Vect2(280.f, 50.f));
	mTitleText->SetText(L"");
	mTitleText->SetColor(RGB(255, 255, 255));
	mTitleText->SetFontSize(24);
	this->AddChild(mTitleText);

	mSelectBtn = new CBtnUI;
	mSelectBtn->SetPos(Vect2(0.f, 100.f));
	mSelectBtn->SetScale(Vect2(200.f, 50.f));
	mSelectBtn->SetText(L"����");
	mSelectBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	mSelectBtn->SetClickedCallBack(this, (OBJECT_FUNC)&LevelupUI::ApplyLevelUp);
	this->AddChild(mSelectBtn);
}

LevelupUI::~LevelupUI()
{
}


void LevelupUI::SetTitle(const wstring& _str)
{
	mTitleText->SetText(_str);
}

void LevelupUI::ApplyLevelUp()
{
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();

	switch (mEffect)
	{
	case LEVELUP_EFFECT::FULL_HP_UP:					// �ִ� ü�� ����
		pPlayer->mtInfo.fullHP += 10.f;
		break;
	case LEVELUP_EFFECT::REGENERATION_HP_UP:			// ü�� ��� ����
		pPlayer->mtInfo.regenerationHP += 10.f;
		break;
	case LEVELUP_EFFECT::MOVE_SPEED_UP:					// �̵��ӵ� ����
		pPlayer->mtInfo.moveSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::ATK_DAMAGE_UP:					// ���ݷ� ����
		pPlayer->mtInfo.atkDamage += 15.f;
		break;
	case LEVELUP_EFFECT::ATK_SPEED_UP:					// ���ݼӵ� ����
		pPlayer->mtInfo.atkSpeed += 10.f;
		break;
	case LEVELUP_EFFECT::ATK_RANGE_UP:					// ��Ÿ� ����
		pPlayer->mtInfo.atkRange += 100.f;
		break;
	case LEVELUP_EFFECT::SHOT_SPEED_UP:					// ź�� ����
		pPlayer->mtInfo.shotSpeed += 50.f;
		break;
	case LEVELUP_EFFECT::RELOAD_SPEED_UP:				// �����ӵ� ����
		pPlayer->mtInfo.reloadSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::SHOT_ANGLE_UP:					// ���߷� ����
		pPlayer->mtInfo.shotAngle += 10.f;
		break;
	case LEVELUP_EFFECT::SHOT_COUNT_UP:					// �߻�Ǵ� ź�� �� ����
		pPlayer->mtInfo.shotCount += 2.f;
		break;
	case LEVELUP_EFFECT::PENETRATION_UP:				// ���� �����ϴ� Ƚ�� ����
		pPlayer->mtInfo.penetration += 1;
		break;
	case LEVELUP_EFFECT::SPLITCOUNT_UP:					// �п��Ǵ� �Ѿ� ���� ����
		pPlayer->mtInfo.splitCount += 1;
		break;
	case LEVELUP_EFFECT::BOUNTCECOUNT_UP:				// ���� ƨ��� Ƚ�� ����
		pPlayer->mtInfo.bounceCount += 1;
		break;
	}

	CTimeMgr::GetI()->Play();
	CUIMgr::GetI()->SetFocusUI(nullptr);
	LevelupUIMgr::GetI()->Delete();
}
