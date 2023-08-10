#include "pch.h"
#include "GameOverUI.h"

#include "CCore.h"
#include "CTimeMgr.h"

#include "TextUI.h"
#include "CBtnUI.h"
#include "GUIMgr.h"
#include "CColumn.h"
#include "CImageUI.h"

#include "CTexture.h"
#include "CResMgr.h"

GameOverUI::GameOverUI()
	: CImageUI()
	, mpTitle(nullptr)
	, mpMainSceneBtn(nullptr)
	, mFadeDelay(0.7f)
	, mCurDelay(0.f)
	, mbFade(false)
{
	SetScale(CCore::GetI()->GetResolution());
	SetColor(RGB(0, 0, 0));

	CColumn* pCol = new CColumn;
	pCol->SetPos(Vect2::zero);
	pCol->SetSpacing(28.f);
	pCol->SetScale(CCore::GetI()->GetResolution());
	this->AddChild(pCol);

	mpTitle = new TextUI;
	mpTitle->SetRaycastTarget(false);
	mpTitle->SetText(L"YOU DIE");
	mpTitle->SetPos(Vect2::zero);
	mpTitle->SetFontSize(100.f);
	mpTitle->SetColor(RGB(255, 255, 255));
	mpTitle->SetScale(Vect2(0.f, 100.f));
	pCol->AddChild(mpTitle);

	mpMainSceneBtn = new CBtnUI;
	mpMainSceneBtn->SetScale(Vect2(150.f, 50.f));
	mpMainSceneBtn->SetText(L"메인화면");
	mpMainSceneBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Button_3", L"texture\\ui\\button\\3.bmp"));
	mpMainSceneBtn->SetClickedCallBack(this, (OBJECT_FUNC)&GameOverUI::Close);
	pCol->AddChild(mpMainSceneBtn);
}

GameOverUI::~GameOverUI()
{
}




void GameOverUI::Close()
{
	GUIMgr::GetI()->CloseGameOverUI();
	ChangeScene(SCENE_TYPE::MAIN);
}

void GameOverUI::Show()
{
	GUIMgr::GetI()->ShowGameOverUI();
}


void GameOverUI::Update()
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


void GameOverUI::Build()
{
}

