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
	SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Panel_1", L"texture\\ui\\panel_1.bmp"));

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
	mSelectBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
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
		pPlayer->mtPlayerInfo.mFullHP += 10.f;
		break;
	case LEVELUP_EFFECT::REGENERATION_HP_UP:			// ü�� ��� ����
		pPlayer->mtPlayerInfo.mRegenerationHP += 10.f;
		break;
	case LEVELUP_EFFECT::MOVE_SPEED_UP:					// �̵��ӵ� ����
		pPlayer->mtPlayerInfo.mMoveSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::ATK_DAMAGE_UP:					// ���ݷ� ����
		pPlayer->mtPlayerInfo.mAtkDamage += 15.f;
		break;
	case LEVELUP_EFFECT::ATK_SPEED_UP:					// ���ݼӵ� ����
		pPlayer->mtPlayerInfo.mAtkSpeed += 10.f;
		break;
	case LEVELUP_EFFECT::ATK_RANGE_UP:					// ��Ÿ� ����
		pPlayer->mtPlayerInfo.mAtkRange += 100.f;
		break;
	case LEVELUP_EFFECT::SHOT_SPEED_UP:					// ź�� ����
		pPlayer->mtPlayerInfo.mShotSpeed += 50.f;
		break;
	case LEVELUP_EFFECT::RELOAD_SPEED_UP:				// �����ӵ� ����
		pPlayer->mtPlayerInfo.mReloadSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::SHOT_ANGLE_UP:					// ���߷� ����
		pPlayer->mtPlayerInfo.mShotAngle += 10.f;
		break;
	case LEVELUP_EFFECT::SHOT_COUNT_UP:					// �߻�Ǵ� ź�� �� ����
		pPlayer->mtPlayerInfo.mShotCount += 2.f;
		break;
	case LEVELUP_EFFECT::PENETRATION_UP:				// ���� �����ϴ� Ƚ�� ����
		pPlayer->mtPlayerInfo.mPenetration += 1;
		break;
	case LEVELUP_EFFECT::SPLITCOUNT_UP:					// �п��Ǵ� �Ѿ� ���� ����
		pPlayer->mtPlayerInfo.mSplitCount += 1;
		break;
	case LEVELUP_EFFECT::BOUNTCECOUNT_UP:				// ���� ƨ��� Ƚ�� ����
		pPlayer->mtPlayerInfo.mBounceCount += 1;
		break;
	}

	CTimeMgr::GetI()->Play();
	CUIMgr::GetI()->SetFocusUI(nullptr);
	LevelupUIMgr::GetI()->Delete();
}
