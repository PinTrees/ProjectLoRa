#include "pch.h"
#include "ClearUI.h"

#include "CCore.h"

#include "TextUI.h"
#include "CColumn.h"
#include "CBtnUI.h"
#include "CTimeMgr.h"
#include "CRow.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "PlayerMgr.h"
#include "Player.h"
#include "Skill.h"


ClearUI::ClearUI()
	: CImageUI()
	, mpTitle(nullptr)
	, mFadeDelay(0.7f)
	, mCurDelay(0.f)
	, mbFade(false)
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	SetColor(RGB(0, 0, 0));
	SetScale(vRes);

	/// 세로 정렬 UI ----------------
	CColumn* pCol = new CColumn;
	pCol->SetScale(vRes);
	pCol->SetSpacing(32.f);
	AddChild(pCol);

	/// 타이틀 UI ------------------------------
	mpTitle = new TextUI;
	mpTitle->SetScale(Vect2(0.f, 80.f));
	mpTitle->SetFontSize(80.f);
	mpTitle->SetColor(RGB(255, 255, 255));
	mpTitle->SetText(L"Clear");
	pCol->AddChild(mpTitle);


	/// 획득한 스킬 UI ------------------------
	mpSkillTitle = new TextUI;
	mpSkillTitle->SetScale(Vect2(0.f, 28.f));
	mpSkillTitle->SetFontSize(28.f);
	mpSkillTitle->SetColor(RGB(255, 255, 255));
	mpSkillTitle->SetText(L"획득한 스킬 목록");
	pCol->AddChild(mpSkillTitle);

	mpSkillListUI = new CRow;
	mpSkillListUI->SetScale(Vect2(100.f, 38.f));
	mpSkillListUI->SetSpacing(8.f);
	mpSkillListUI->SetAlignment(ALIGNMENT::CENTER);
	pCol->AddChild(mpSkillListUI);

	/// 나가기 버튼 ---------------------------
	mpExiteBtn = new CBtnUI;
	mpExiteBtn->SetScale(Vect2(150.f, 50.f));
	mpExiteBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_3", L"texture\\ui\\button\\3.bmp"));
	mpExiteBtn->SetText(L"나가기");
	mpExiteBtn->SetClickedCallBack(this, (OBJECT_FUNC)&ClearUI::changeMainScene);
	pCol->AddChild(mpExiteBtn);
}

ClearUI::~ClearUI()
{
}



void ClearUI::Show()
{
}

void ClearUI::Close()
{
}


void ClearUI::Build()
{
	Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
	auto vecSkillList = pPlayer->GetSkillList();
	
	for (int i = 0; i < vecSkillList.size(); ++i)
	{
		Skill* pSkill = vecSkillList[i]; 

		CColumn* pSkillUI = new CColumn;
		pSkillUI->SetAlignment(ALIGNMENT::CENTER);
		pSkillUI->SetScale(Vect2(48.f, 64.f));

		CImageUI* pIcon = new CImageUI;
		pIcon->SetScale(Vect2(38.f, 38.f));
		pIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Skill_Icon_" + pSkill->GetIconStr(), L"texture\\icon\\" + pSkill->GetIconStr()));
		pSkillUI->AddChild(pIcon);

		TextUI* pLevelText = new TextUI;
		pLevelText->SetColor(RGB(255, 255, 255));
		pLevelText->SetText(std::to_wstring(pSkill->GetSkillLevel()));
		pLevelText->SetOutlineWidth(2.f);
		pLevelText->SetOutlineColor(RGB(0, 0, 0));
		pLevelText->SetFontSize(28.f);
		pSkillUI->AddChild(pLevelText);

		mpSkillListUI->AddChild(pSkillUI);
	}
}


void ClearUI::Update()
{
	CUI::Update();

	if (!IsVisible())
		return;

	if (mbFade)
		return;

	mCurDelay += DT;

	if (mCurDelay >= mFadeDelay) {
		mCurDelay = mFadeDelay;
		mbFade = true;
	}

	float ratio = mCurDelay / mFadeDelay;
	SetAlpha(180 * ratio);
}


void ClearUI::changeMainScene()
{
	ChangeScene(SCENE_TYPE::MAIN);
}

