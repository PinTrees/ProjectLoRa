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
	// 새로운 UI 틀을 제작해야할 경우 해당들의 자식 UI 정보가 크게 변하지 않을 경우 직접 변수에 할당및 자식으로 추가
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
	mSelectBtn->SetText(L"선택");
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
	case LEVELUP_EFFECT::FULL_HP_UP:					// 최대 체력 증가
		pPlayer->mtInfo.fullHP += 10.f;
		break;
	case LEVELUP_EFFECT::REGENERATION_HP_UP:			// 체력 재생 증가
		pPlayer->mtInfo.regenerationHP += 10.f;
		break;
	case LEVELUP_EFFECT::MOVE_SPEED_UP:					// 이동속도 증가
		pPlayer->mtInfo.moveSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::ATK_DAMAGE_UP:					// 공격력 증가
		pPlayer->mtInfo.atkDamage += 15.f;
		break;
	case LEVELUP_EFFECT::ATK_SPEED_UP:					// 공격속도 증가
		pPlayer->mtInfo.atkSpeed += 10.f;
		break;
	case LEVELUP_EFFECT::ATK_RANGE_UP:					// 사거리 증가
		pPlayer->mtInfo.atkRange += 100.f;
		break;
	case LEVELUP_EFFECT::SHOT_SPEED_UP:					// 탄속 증가
		pPlayer->mtInfo.shotSpeed += 50.f;
		break;
	case LEVELUP_EFFECT::RELOAD_SPEED_UP:				// 장전속도 증가
		pPlayer->mtInfo.reloadSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::SHOT_ANGLE_UP:					// 명중률 증가
		pPlayer->mtInfo.shotAngle += 10.f;
		break;
	case LEVELUP_EFFECT::SHOT_COUNT_UP:					// 발사되는 탄알 수 증가
		pPlayer->mtInfo.shotCount += 2.f;
		break;
	case LEVELUP_EFFECT::PENETRATION_UP:				// 적을 관통하는 횟수 증가
		pPlayer->mtInfo.penetration += 1;
		break;
	case LEVELUP_EFFECT::SPLITCOUNT_UP:					// 분열되는 총알 개수 증가
		pPlayer->mtInfo.splitCount += 1;
		break;
	case LEVELUP_EFFECT::BOUNTCECOUNT_UP:				// 벽을 튕기는 횟수 증가
		pPlayer->mtInfo.bounceCount += 1;
		break;
	}

	CTimeMgr::GetI()->Play();
	CUIMgr::GetI()->SetFocusUI(nullptr);
	LevelupUIMgr::GetI()->Delete();
}
