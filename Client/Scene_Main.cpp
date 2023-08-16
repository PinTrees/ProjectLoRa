#include "pch.h"
#include "Scene_Main.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSoundMgr.h"

// UI Header
#include "CBtnUI.h"
#include "CResMgr.h"
#include "CPanelUI.h"
#include "CColumn.h"
#include "CImageUI.h"
#include "CWrap.h"
#include "CScrollView.h"
#include "HelpDialogUI.h"

#include "DatabaseMgr.h"

// Resource Header
#include "CSprite.h"
#include "CSound.h"

// Core Manager Header
#include "UIMgr.h"

#include "CCore.h"


void ChangeSceneStart(DWORD_PTR, DWORD_PTR);
void ChangeSceneTool(DWORD_PTR, DWORD_PTR);



Scene_Main::Scene_Main()
	: mPressBack(nullptr)
	, mFadeDelay(0.5f)
	, mCurDelay(0.f)
	, mFadeDir(1)
	, mpPlayerThumb(nullptr)
	, mDialogHelp(nullptr)
	, mpMainBGM(nullptr)
{
	mpMainBGM = CResMgr::GetI()->LoadSound(L"Bgm_Main", L"sound\\bgm_main.wav");
}


Scene_Main::~Scene_Main()
{
	mpMainBGM = nullptr;
	DatabaseMgr::Dispose();
}



void Scene_Main::Enter()
{
	DatabaseMgr::GetI()->Init();

	if (mpMainBGM)
		mpMainBGM->Play();

	Vect2 vRes = CCore::GetI()->GetResolution();
	
	CSprite* pPanelSprite = CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.png");
	pPanelSprite->SetRenderMode(SPRITE_RENDER_TYPE::POINT);

	// 배경 이미지 생성 -----------------------------------------------------
	CImageUI* pBackground = new CImageUI;
	pBackground->SetRaycastTarget(false);
	pBackground->SetScale(vRes);
	pBackground->SetPos(vRes * 0.5f);
	pBackground->SetTexture(CResMgr::GetI()->LoadTexture(L"Background_Start", L"texture\\background\\start.bmp"));
	AddObject(pBackground, GROUP_TYPE::UI);
	// ---------------------------------------------------------------------

	mpPlayerThumb = new CImageUI;
	mpPlayerThumb->SetPos(Vect2(vRes.x * 0.38f, vRes.y * 0.68f));
	mpPlayerThumb->SetScale(Vect2(83.f, 140.f) * 1.4f);
	mpPlayerThumb->SetTexture(CResMgr::GetI()->LoadTexture(L"Player_Thumb", L"texture\\player\\thumb.bmp"));
	AddObject(mpPlayerThumb, GROUP_TYPE::UI);

	// 설정 버튼 생성 -------------------------------------------------------
	Vect2 vBtnSize = Vect2(36.f, 36.f);

	CColumn* pHCol = new CColumn;
	pHCol->SetFixedChildMouseCheck(false);
	pHCol->SetPos(Vect2(vRes.x - vBtnSize.x, vRes.y - 250.f - vBtnSize.y * 0.5f));
	pHCol->SetScale(Vect2(36.f, 500.f));
	pHCol->SetAlignment(ALIGNMENT::BOTTOM_CENTER);
	pHCol->SetSpacing(12.f);
	AddObject(pHCol, GROUP_TYPE::UI);

	CBtnUI* pSettingButton = new CBtnUI;
	pSettingButton->SetScale(vBtnSize);
	pSettingButton->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Setting_W", L"texture\\ui\\icon\\setting_w.bmp"));
	pSettingButton->SetClickedCallBack(&ChangeSceneTool, 0, 0);
	pHCol->AddChild(pSettingButton);

	CBtnUI* pSkillInfoBtn = new CBtnUI;
	pSkillInfoBtn->SetScale(vBtnSize);
	pSkillInfoBtn->SetOriginalMouseCheck(true);
	pSkillInfoBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Q_W", L"texture\\ui\\icon\\q.bmp"));
	pSkillInfoBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Main::OpenHelpDialog);
	pHCol->AddChild(pSkillInfoBtn);

	CBtnUI* pHelpBtn = new CBtnUI;
	pHelpBtn->SetScale(vBtnSize);
	pHelpBtn->SetOriginalMouseCheck(true);
	pHelpBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Q_W", L"texture\\ui\\icon\\q.bmp"));
	pHelpBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Main::OpenInfoDialog);
	pHCol->AddChild(pHelpBtn);
	// ---------------------------------------------------------------------

	CColumn* pCol = new CColumn;
	pCol->SetPos(vRes * 0.5f);
	pCol->SetScale(Vect2(400.f, 700.f));
	pCol->SetSpacing(100.f);
	AddObject(pCol, GROUP_TYPE::UI);

	// 타이틀 텍스트 생성 ---------------------------------------------------
	TextUI* pTitleText = new TextUI;
	pTitleText->SetScale(Vect2(0.f, 100.f));
	pTitleText->SetFontSize(80.f);
	pTitleText->SetText(L"The RoLa");
	pTitleText->SetOutlineWidth(3.f);
	pTitleText->SetOutlineColor(RGB(0, 0, 0));
	pTitleText->SetColor(RGB(255, 255, 255));
	pCol->AddChild(pTitleText);
	// ---------------------------------------------------------------------

	// 게임 시작 텍스트 생성 ---------------------------------------------------
	mPressBack = new CImageUI;
	mPressBack->SetRaycastTarget(false);
	mPressBack->SetScale(Vect2(400.f, 45.f));
	mPressBack->SetPos(vRes * 0.5f);
	mPressBack->SetColor(RGB(0, 0, 0));
	mPressBack->SetAlpha(100);
	pCol->AddChild(mPressBack);

	TextUI* pStartText = new TextUI;
	pStartText->SetScale(Vect2(0.f, 100.f));
	pStartText->SetFontSize(28.f);
	pStartText->SetText(L"Press Space To Start");
	pStartText->SetOutlineWidth(1.f);
	pStartText->SetOutlineColor(RGB(150, 150, 150));
	pStartText->SetColor(RGB(255, 255, 255));
	mPressBack->AddChild(pStartText);
	// ---------------------------------------------------------------------

	// 게임 시작 버튼 생성 ---------------------------------------------------
	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vect2(200.f, 50.f));
	pGameStartBtn->SetText(L"Play");
	pGameStartBtn->SetAlpha(150);
	pGameStartBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_3", L"texture\\ui\\button\\3.bmp"));
	pGameStartBtn->SetClickedCallBack(&ChangeSceneStart, 0, 0);
	pCol->AddChild(pGameStartBtn);
	// ---------------------------------------------------------------------

	// 게임 도움말 다이얼로그 생성 -------------------------------------------
	mDialogHelp = new HelpDialogUI;
	mDialogHelp->SetPos(vRes * 0.5f);
	AddObject(mDialogHelp, GROUP_TYPE::UI);

	CloseInfoDialog();
	// ---------------------------------------------------------------------
}


void Scene_Main::Update()
{
	CScene::Update();

	mCurDelay += DT * mFadeDir;

	if (mCurDelay >= mFadeDelay) {
		mFadeDir = -1;
	}
	else if (mCurDelay <= 0) {
		mFadeDir = 1;
	}

	float ratio = (mCurDelay / mFadeDelay);
	mPressBack->SetAlpha((int)(50 * ratio) + 50);

	if (KEY_TAP(KEY::SPACE)) {
		ChangeSceneStart(0, 0);
	}
}


void Scene_Main::Exit()
{
	mpMainBGM->Stop();
	DeleteAll();
}



void Scene_Main::OpenHelpDialog()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetFixedPos(false);
	pPanelUI->SetScale(Vect2(500.f, 500.f));
	pPanelUI->SetPos(Vect2(vRes.x * 0.5f, vRes.y * 0.5f));
	pPanelUI->SetTexture(CResMgr::GetI()->LoadSprite(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));


	CScrollView* pScrollView = new CScrollView;
	pScrollView->SetPos(Vect2(0.f, 25.f));
	pScrollView->SetScale(Vect2(pPanelUI->GetScale().x * 0.85f, 350.f));
	pPanelUI->AddChild(pScrollView);

	CWrap* pWrap = new CWrap;
	pWrap->SetPos(Vect2(0.f, 128.f));
	pWrap->SetScale(Vect2(pScrollView->GetScale().x, 650.f));
	pScrollView->AddChild(pWrap);

	for (int i = 0; i < 100; ++i)
	{
		CImageUI* pImg = new CImageUI;
		pImg->SetScale(Vect2(38.f, 38.f));
		pImg->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Item_" + std::to_wstring(i + 1), L"texture\\item\\26_" + std::to_wstring(i + 1) + L".bmp"));
		pWrap->AddChild(pImg);
	}

	CBtnUI* pCloseBtn = new CBtnUI;
	pCloseBtn->SetPos(Vect2(0.f, 200.f));
	pCloseBtn->SetScale(Vect2(150.f, 42.f));
	pCloseBtn->SetText(L"닫기");
	pCloseBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Btn_3", L"texture\\ui\\button\\3.bmp"));
	pCloseBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Main::CloseItemDataUI);
	pPanelUI->AddChild(pCloseBtn);

	mItemUI = pPanelUI;
	CreateObject(mItemUI, GROUP_TYPE::UI);
}


void Scene_Main::CloseItemDataUI()
{
	if (nullptr == mItemUI)
		return;

	CUIMgr::GetI()->SetFocusUI(nullptr);
	DeleteObject(mItemUI);
	mItemUI = nullptr;
}


void Scene_Main::OpenInfoDialog()
{
	mDialogHelp->SetVisible(true);
	CUIMgr::GetI()->SetTop(mDialogHelp);
}

void Scene_Main::CloseInfoDialog()
{
	mDialogHelp->SetVisible(false);
}



void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}
void ChangeSceneTool(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TOOL);
}


