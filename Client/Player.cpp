#include "pch.h"
#include "Player.h"

#include "CCore.h"

// Core Manager Header
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "Random.h"
#include "UIMgr.h"

// Component Header
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "RigidBody.h"
#include "CScene.h"
#include "CSound.h"

// GameObject Header
#include "Bullet.h"

// UI Object Header
#include "CUI.h"
#include "BarUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "TextUI.h"
#include "CRow.h"
#include "CImageUI.h"

#include "CState.h"

#include "Skill.h"

// Game Manager Header
#include "HubUIMgr.h"
#include "LevelUpUIMgr.h"
#include "PlayerMgr.h"
#include "CSoundMgr.h"



Player::Player()
	: mfCurDelay(0.f)
	, mfDelay(0.03f)
	, mvDir(Vect2(0.f, 0.f))
	, mExpBar(nullptr)
	, mLevel(0)
	, mExp(0.f)
	, mAI(nullptr)
	, mtInfo({})
	, mVecSkill({})
	, mVecMaxLevelSkill{}
	, mpCoinSound(nullptr)
{
	// Load ----------------------
	mpCoinSound = CResMgr::GetI()->LoadSound(L"Sound_Coin", L"sound\\coin.wav");
	mpLevelUpSound = CResMgr::GetI()->LoadSound(L"Sound_Clear", L"sound\\clear.wav");

	mtInfo.fullHP = 100.f;
	mtInfo.curHp = mtInfo.fullHP;

	// Init Object Component
	// Create Collider Component
	CreateCollider();
	GetCollider()->SetOffsetPos(Vect2(-12.f, -8.f));
	GetCollider()->SetScale(Vect2(30.f, 45.f));

	// Create RigidBody Component
	CreateRigidBody();
	GetRigidBody()->SetMess(1.f);
	GetRigidBody()->SetMaxVelocity(Vect2(200.f, 200.f));
	GetRigidBody()->SetAccelAlpha(Vect2(100.f, 100.f));

	// Create Animator Component
	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player_idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_run_r.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_run_l.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_atk_r.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_atk_l.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_dash_r.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_die.anim");
	GetAnimator()->Play(L"IDLE", true);

	SetScale(Vect2(73.f, 54.f) * 1.5f);
	SetPivot(Vect2(-15.f, 15.f));
	SetName(L"Player");

	Vect2 vRes = CCore::GetI()->GetResolution();

	// Exp Bar
	mExpBar = new BarUI;
	mExpBar->SetCameraAffected(true);
	mExpBar->SetScale(Vect2(vRes.x, 8.f));
	mExpBar->SetPos(Vect2(vRes.x * 0.5f, vRes.y - mExpBar->GetScale().y * 0.5f));
	mExpBar->SetColor(RGB(255, 222, 0));
	CreateObject(mExpBar, GROUP_TYPE::UI);

	// Player HP UI Parent
	CRow* pRow = new CRow;
	pRow->SetScale(Vect2(400.f, 50.f));
	pRow->SetPos(Vect2(pRow->GetScale() * 0.5f) + Vect2(28.f, 28.f));
	pRow->SetSpacing(8.f);
	pRow->SetAlignment(ALIGNMENT::CENTER_LEFT);
	CreateObject(pRow, GROUP_TYPE::UI);

	// HP Icon
	CImageUI* pIcon = new CImageUI;
	pIcon->SetScale(Vect2(36.f, 36.f));
	pIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Hp", L"texture\\ui\\icon\\hp.bmp"));
	pRow->AddChild(pIcon);

	// HP Bar 
	CImageUI* pHpBarUI = new CImageUI;
	pHpBarUI->SetScale(Vect2(200.f, 36.f));
	pHpBarUI->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar_Background", L"texture\\ui\\hp_bar\\hp_background.bmp"));
	pRow->AddChild(pHpBarUI);

	mHpBar = new CImageUI;
	mHpBar->SetScale(pHpBarUI->GetScale());
	mHpBar->SetImageType(IMAGE_TYPE::FILLED);
	mHpBar->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar", L"texture\\ui\\hp_bar\\hp_bar.bmp"));
	pHpBarUI->AddChild(mHpBar);

	CImageUI* pHpBarFrame = new CImageUI;
	pHpBarFrame->SetScale(pHpBarUI->GetScale());
	pHpBarFrame->SetTexture(CResMgr::GetI()->LoadTexture(L"Hp_Bar_Frame", L"texture\\ui\\hp_bar\\hp_bar_frame.bmp"));
	pHpBarUI->AddChild(pHpBarFrame);

	mHpText = new TextUI;
	mHpText->SetText(L"0");
	mHpText->SetFontSize(20);
	mHpText->SetColor(RGB(255, 255, 255));
	mHpText->SetOutlineColor(RGB(0, 0, 0));
	mHpText->SetOutlineWidth(1);
	pHpBarUI->AddChild(mHpText);
}


Player::~Player()
{
	if (nullptr != mAI)
		delete mAI;

	mpCoinSound = nullptr;
	mpLevelUpSound = nullptr;
}




void Player::Update()
{
	if (mAI)
		mAI->Update();

	GetAnimator()->Update();
	 
	calExp();
	mfCurDelay += DT;

	/// 최상단 예외 처리
	if (mAI->GetCurStateType() == PLAYER_STATE::DIE)
	{
		return;
	}

	if (mfCurDelay > mtInfo.atkDelay) {
		if (GetAI()->GetCurStateType() != PLAYER_STATE::ATTACK) {
			mfCurDelay = 0;
			ChangeAIState(GetAI(), PLAYER_STATE::ATTACK);
		}
	}

	UseSkill();

	Vect2 vPos = GetPos();
	mExpBar->SetFillAmount(GetExp() / GetMaxExp());
	mHpBar->SetFilledAmount(mtInfo.curHp / mtInfo.fullHP);
	mHpText->SetText(std::to_wstring(mtInfo.curHp));

	if (mtInfo.curHp <= 0)
	{
		ChangeAIState(GetAI(), PLAYER_STATE::DIE);
		return;
	}


	if (mAI->GetCurStateType() == PLAYER_STATE::DASH)
		return;


	if (KEY_TAP(KEY::SPACE))
	{
		ChangeAIState(GetAI(), PLAYER_STATE::DASH);
		return;
	}

	mvDir = Vect2::zero;

	if (KEY_HOLD(KEY::W)) mvDir += Vect2::up;
	if (KEY_HOLD(KEY::S)) mvDir += Vect2::down;
	if (KEY_HOLD(KEY::A)) mvDir += Vect2::left;
	if (KEY_HOLD(KEY::D)) mvDir += Vect2::right;

	if (KEY_HOLD(KEY::Q)) mtInfo.curHp = 100.f;

	if (mvDir != Vect2::zero)
	{
		if (GetAI()->GetCurStateType() != PLAYER_STATE::RUN)
			ChangeAIState(GetAI(), PLAYER_STATE::RUN);
	}
	else if (GetAI()->GetCurStateType() != PLAYER_STATE::IDLE
		&& GetAI()->GetCurStateType() != PLAYER_STATE::ATTACK)
	{
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void Player::Render(HDC _dc)
{
	//컴포넌트 ( 충돌체, ect...	) 가 있는경우 랜더
	CompnentRender(_dc);
}


void Player::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Gold")
	{
		PlayerMgr::GetI()->AddGold(5);
		HubUIMgr::GetI()->BuildGoldText();

		if (mpCoinSound)
			mpCoinSound->Play();
	}
}


void Player::calExp()
{
	if (mExp >= GetMaxExp())
	{
		++mLevel;
		mExp = 0;

		if (mpLevelUpSound)
			mpLevelUpSound->Play();

		HubUIMgr::GetI()->SetLevelText(mLevel);
		LevelUpUIMgr::GetI()->Choice();
	}
}


Skill* Player::FindSkill(SKILL_TYPE type)
{
	Skill* result = nullptr;

	for (int i = 0; i < mVecSkill.size(); ++i)
	{
		if (mVecSkill[i]->GetType() == type)
		{
			result = mVecSkill[i];
			break;
		}
	}

	return result;
}

void Player::AddSkill(Skill* _skill)
{
	auto skill = FindSkill(_skill->GetType());

	if (nullptr == skill)
	{
		_skill->AddSkillLevel();
		mVecSkill.push_back(_skill);
	}
	else
	{
		skill->AddSkillLevel();

		if (skill->GetSkillLevel() == skill->GetMaxSkillLv())
		{
			mVecMaxLevelSkill.push_back(skill->GetType());
		}
	}

	HubUIMgr::GetI()->BuildSkillUI(mVecSkill);
}



void Player::UseSkill()
{
	for (size_t i = 0; i < mVecSkill.size(); ++i)
	{
		mVecSkill[i]->CheckAvailable();
		if (mVecSkill[i]->GetAvilable())
		{
			mVecSkill[i]->UseSkill();
			mVecSkill[i]->SetAvailable(false);
		}

		mVecSkill[i]->Update();
	}
}
