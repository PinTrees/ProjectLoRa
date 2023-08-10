#include "pch.h"
#include "GUIMgr.h"

#include "CTimeMgr.h"

#include "SettingUI.h"

#include "CResMgr.h"

#include "CCore.h"
#include "CImageUI.h"
#include "CBtnUI.h"
#include "TextUI.h"
#include "CColumn.h"
#include "GameOverUI.h"
#include "ClearUI.h"

#include "UIMgr.h"



SINGLE_HEADER(GUIMgr);


GUIMgr::GUIMgr()
	: mpSettinUI(nullptr)
	, mpBackground(nullptr)
	, mFrameText(nullptr)
{
}

GUIMgr::~GUIMgr()
{
}


void GUIMgr::Init()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	mpBackground = new CImageUI;
	mpBackground->SetPos(vRes * 0.5f);
	mpBackground->SetScale(vRes);
	mpBackground->SetColor(RGB(0, 0, 0));
	mpBackground->SetRaycastTarget(false);
	CreateObject(mpBackground, GROUP_TYPE::UI);

	/// 커스텀 UI 생성 ----------------------------
	mpSettinUI = new SettingUI;
	mpSettinUI->SetPos(vRes * 0.5f);
	CreateObject(mpSettinUI, GROUP_TYPE::UI);

	mpGameOverUI = new GameOverUI;
	mpGameOverUI->SetPos(vRes * 0.5f);
	CreateObject(mpGameOverUI, GROUP_TYPE::UI); 

	mpGameClearUI = new ClearUI;
	mpGameClearUI->SetPos(vRes * 0.5f);
	CreateObject(mpGameClearUI, GROUP_TYPE::UI);
	/// ------------------------------------------


	/// 타이머 UI 생성 ----------------------------
	mTimerText = new TextUI;
	mTimerText->SetPos(Vect2(vRes.x * 0.5f, 50.f));
	mTimerText->SetScale(Vect2(0.f, 50.f));
	mTimerText->SetText(L"00:00");
	mTimerText->SetColor(RGB(255, 255, 255));
	mTimerText->SetFontSize(48);
	CreateObject(mTimerText, GROUP_TYPE::UI);
	/// ------------------------------------------

	mFrameText = new TextUI;
	mFrameText->SetPos(Vect2(vRes.x - 80.f, 100.f));
	mFrameText->SetScale(Vect2(100.f, 30.f));
	mFrameText->SetColor(RGB(0, 255, 255));
	mFrameText->SetText(L"FPS");
	mFrameText->SetFontSize(24.f);
	CreateObject(mFrameText, GROUP_TYPE::UI);


	mpSettingBtn = new CBtnUI;
	mpSettingBtn->SetScale(Vect2(50.f, 50.f));
	mpSettingBtn->SetPos(Vect2(vRes.x - 50.f, 50.f));
	mpSettingBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Button_2", L"texture\\ui\\button\\2.bmp"));
	mpSettingBtn->SetClickedCallBack(mpSettinUI, OBJECT_FUNC(&SettingUI::Show));
	CreateObject(mpSettingBtn, GROUP_TYPE::UI);

	CImageUI* pImage = new CImageUI;
	pImage->SetPos(Vect2(0.f, -5.f));
	pImage->SetScale(mpSettingBtn->GetScale() * 0.6f);
	pImage->SetTexture(CResMgr::GetI()->LoadTexture(L"Setting_Icon", L"texture\\ui\\icon\\setting.bmp"));
	pImage->SetRaycastTarget(false);
	mpSettingBtn->AddChild(pImage);


	CloseSettingUI();
	CloseGameOverUI();
	CloseGameClearUI();
}

void GUIMgr::ShowSettingUI()
{
	CTimeMgr::GetI()->Stop();
	mpBackground->SetAlpha(150);
	mpBackground->SetVisible(true);
	mpSettinUI->SetVisible(true);
	mpSettinUI->Build();
}

void GUIMgr::CloseSettingUI()
{
	CTimeMgr::GetI()->Play();
	mpBackground->SetVisible(false);
	mpSettinUI->SetVisible(false);
}


// -----------------------------------------------------
// 게임 오버 UI -----------------------------------------
void GUIMgr::ShowGameOverUI()
{
	CTimeMgr::GetI()->Stop();
	mpGameOverUI->SetVisible(true);
	mpGameOverUI->Build();

	CUIMgr::GetI()->SetTop(mpGameOverUI);
}

void GUIMgr::CloseGameOverUI()
{
	CTimeMgr::GetI()->Play();
	mpGameOverUI->SetVisible(false);
}
// -----------------------------------------------------



// -------------------------------------------------------
// 게임 클리어 UI -----------------------------------------
void GUIMgr::ShowGameClearUI()
{
	CTimeMgr::GetI()->Stop();
	mpGameClearUI->SetVisible(true);
	mpGameClearUI->Build();
	CUIMgr::GetI()->SetTop(mpGameClearUI);
}

void GUIMgr::CloseGameClearUI()
{
	CTimeMgr::GetI()->Play();
	mpGameClearUI->SetVisible(false);
}
// -------------------------------------------------------




void GUIMgr::SetFrameText(UINT frame)
{
	mFrameText->SetText(std::to_wstring(frame) + L" FPS");
}


void GUIMgr::SetTimerText(UINT timer)
{
	int minute = timer / 60;
	int second = timer % 60;
	mTimerText->SetText(std::to_wstring(minute) + L":" + std::to_wstring(second));
}
