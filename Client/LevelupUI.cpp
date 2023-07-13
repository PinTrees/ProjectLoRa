#include "pch.h"
#include "LevelupUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CResMgr.h"
#include "TextUI.h"
#include "Player.h"
#include "CTimeMgr.h"
#include "UIMgr.h"
#include "LevelupUIMgr.h"
#include "CFont.h"


LevelupUI::LevelupUI()
	: CUI(false)
	, mEffect()
	, mStrEffect{}
	, mpLeader(nullptr)
	, mpPlayer(nullptr)
{
	
}

LevelupUI::~LevelupUI()
{
}


void LevelupUI::CreateLevelupUI(Player* _player, Vect2 _pos)
{
	mpPlayer = _player;

	mpLeader = new CPanelUI;
	mpLeader->SetPos(Vect2(_pos.x, _pos.y));
	mpLeader->SetScale(Vect2(300.f, 300.f));
	mpLeader->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Panel_1", L"texture\\ui\\panel_1.bmp"));
	
	TextUI* pText = new TextUI;
	pText->SetPos(Vect2(0.f, 0.f));
	pText->SetScale(Vect2(200.f, 50.f));
	pText->SetText(mStrEffect);
	mpLeader->AddChild(pText);

	CBtnUI* pBtn = new CBtnUI;
	pBtn->SetPos(Vect2(0.f, 100.f));
	pBtn->SetScale(Vect2(200.f, 50.f));
	pBtn->SetText(L"����");
	pBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pBtn->SetClickedCallBack(this, (OBJECT_FUNC)&LevelupUI::ApplyLevelUp);
	mpLeader->AddChild(pBtn);

	CreateObject(mpLeader, GROUP_TYPE::UI);
}

void LevelupUI::ApplyLevelUp()
{
	switch (mEffect)
	{
	case LEVELUP_EFFECT::FULL_HP_UP:					// �ִ� ü�� ����
		mpPlayer->mtPlayerInfo.mFullHP += 10.f;
		break;
	case LEVELUP_EFFECT::REGENERATION_HP_UP:			// ü�� ��� ����
		mpPlayer->mtPlayerInfo.mRegenerationHP += 10.f;
		break;
	case LEVELUP_EFFECT::MOVE_SPEED_UP:					// �̵��ӵ� ����
		mpPlayer->mtPlayerInfo.mMoveSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::ATK_DAMAGE_UP:					// ���ݷ� ����
		mpPlayer->mtPlayerInfo.mAtkDamage += 15.f;
		break;
	case LEVELUP_EFFECT::ATK_SPEED_UP:					// ���ݼӵ� ����
		mpPlayer->mtPlayerInfo.mAtkSpeed += 10.f;
		break;
	case LEVELUP_EFFECT::ATK_RANGE_UP:					// ��Ÿ� ����
		mpPlayer->mtPlayerInfo.mAtkRange += 100.f;
		break;
	case LEVELUP_EFFECT::SHOT_SPEED_UP:					// ź�� ����
		mpPlayer->mtPlayerInfo.mShotSpeed += 50.f;
		break;
	case LEVELUP_EFFECT::RELOAD_SPEED_UP:				// �����ӵ� ����
		mpPlayer->mtPlayerInfo.mReloadSpeed += 20.f;
		break;
	case LEVELUP_EFFECT::SHOT_ANGLE_UP:					// ���߷� ����
		mpPlayer->mtPlayerInfo.mShotAngle += 10.f;
		break;
	case LEVELUP_EFFECT::SHOT_COUNT_UP:					// �߻�Ǵ� ź�� �� ����
		mpPlayer->mtPlayerInfo.mShotCount += 2.f;
		break;
	case LEVELUP_EFFECT::PENETRATION_UP:				// ���� �����ϴ� Ƚ�� ����
		mpPlayer->mtPlayerInfo.mPenetration += 1;
		break;
	case LEVELUP_EFFECT::SPLITCOUNT_UP:					// �п��Ǵ� �Ѿ� ���� ����
		mpPlayer->mtPlayerInfo.mSplitCount += 1;
		break;
	case LEVELUP_EFFECT::BOUNTCECOUNT_UP:				// ���� ƨ��� Ƚ�� ����
		mpPlayer->mtPlayerInfo.mBounceCount += 1;
		break;
	}

	CTimeMgr::GetI()->Play();
	CUIMgr::GetI()->SetFocusUI(nullptr);
	LevelupUIMgr::GetI()->Delete();
}
