#include "pch.h"
#include "HubUIMgr.h"

#include "CCore.h"

#include "CAnimator.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CRow.h"
#include "CImageUI.h"
#include "TextUI.h"

#include "Skill.h"

#include "PlayerMgr.h"


SINGLE_HEADER(HubUIMgr);


HubUIMgr::HubUIMgr()
	: mBulletRowUI(nullptr)
	, mReroadUI(nullptr)
	, mpGoldText(nullptr)
	, mpTimeext(nullptr)
{
}


HubUIMgr::~HubUIMgr()
{
	DeleteObject(mBulletRowUI);
}


void HubUIMgr::Init()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	CRow* pRowUI = new CRow;
	pRowUI->SetAlignment(ALIGNMENT::CENTER_LEFT);
	pRowUI->SetPos(vRes - Vect2(200.f, 50.f));
	pRowUI->SetScale(Vect2(350.f, 50.f));
	pRowUI->SetSpacing(-8.f);

	mBulletRowUI = pRowUI;

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"UI_B1", L"texture\\ui\\bullet_1.bmp");

	for (int i = 0; i < 10; ++i)
	{
		CImageUI* bImg = new CImageUI;
		bImg->SetScale(Vect2(40.f, 60.f) * 0.7f);

		bImg->CreateAnimator();
		bImg->GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(32.f, 48.f), Vect2(32.f, 0.f), 0.1f, 4);
		bImg->GetAnimator()->Play(L"IDLE", true);
		mBulletRowUI->AddChild(bImg);
	}

	//CreateObject(mBulletRowUI, GROUP_TYPE::UI);

	mpLevelText = new TextUI;
	mpLevelText->SetPos(Vect2(70.f, vRes.y - 30.f));
	mpLevelText->SetScale(Vect2(100.f, 50.f));
	mpLevelText->SetOutlineWidth(2);
	mpLevelText->SetFontSize(38.f);
	mpLevelText->SetOutlineColor(RGB(0, 0, 0));
	mpLevelText->SetColor(RGB(255, 163, 0));
	mpLevelText->SetText(L"LV 0");
	CreateObject(mpLevelText, GROUP_TYPE::UI);
	
	mpSkillUI = new CRow;
	mpSkillUI->SetPos(Vect2(vRes.x * 0.5f, vRes.y - 50.f));
	mpSkillUI->SetScale(Vect2(200.f, 50.f));
	mpSkillUI->SetSpacing(12.f);
	mpSkillUI->SetAlignment(ALIGNMENT::CENTER);
	CreateObject(mpSkillUI, GROUP_TYPE::UI);

	for (int i = 0; i < 10; ++i)
	{
		CImageUI* icon = new CImageUI;
		icon->SetScale(Vect2(50.f, 50.f));
		icon->SetColor(RGB(255, 255, 255));
		icon->SetVisible(false);
		mpSkillUI->AddChild(icon);
	}

	mpGoldText = new TextUI;
	mpGoldText->SetPos(Vect2(vRes.x - 100.f, vRes.y - 30.f));
	mpGoldText->SetScale(Vect2(0.f, 50.f));
	mpGoldText->SetOutlineWidth(2);
	mpGoldText->SetFontSize(38.f);
	mpGoldText->SetOutlineColor(RGB(127, 64, 21));
	mpGoldText->SetColor(RGB(255, 127, 39));
	mpGoldText->SetText(L"GOLD 0");
	CreateObject(mpGoldText, GROUP_TYPE::UI);
}


void HubUIMgr::SetBulletUI(UINT count)
{
	vector<CUI*> vecBulletUI = mBulletRowUI->GetChild();
	for (int i = 0; i < vecBulletUI.size(); ++i)
	{
		if (i >= (int)count)
		{
			vecBulletUI[i]->SetVisible(false);
		}
		else
		{
			vecBulletUI[i]->SetVisible(true);
		}
	}
}

void HubUIMgr::SetLevelText(int level)
{
	mpLevelText->SetText(L"LV " + std::to_wstring(level));
}


void HubUIMgr::BuildSkillUI(vector<Skill*>& skills)
{
	auto children = mpSkillUI->GetChild();
	for (int i = 0; i < children.size(); ++i) {
		CImageUI* icon = (CImageUI*)children[i];
		
		if (i >= skills.size()) {
			icon->SetVisible(false);
			continue;
		}

		icon->SetTexture(CResMgr::GetI()->LoadTexture(L"Skill_Icon_" + skills[i]->GetIconStr(),
			L"texture\\icon\\" + skills[i]->GetIconStr()));
		icon->SetVisible(true);
	}
}


void HubUIMgr::BuildGoldText()
{
	auto gold = PlayerMgr::GetI()->GetGold();
	mpGoldText->SetText(L"GOLD " + std::to_wstring(gold));
}
