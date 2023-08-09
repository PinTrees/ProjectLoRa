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

	/// Ŀ���� UI ���� ----------------------------
	mpSettinUI = new SettingUI;
	mpSettinUI->SetPos(vRes * 0.5f);
	CreateObject(mpSettinUI, GROUP_TYPE::UI);

	mpGameOverUI = new GameOverUI;
	mpGameOverUI->SetPos(vRes * 0.5f);
	CreateObject(mpGameOverUI, GROUP_TYPE::UI); 
	/// ------------------------------------------


	mFrameText = new TextUI;
	mFrameText->SetPos(Vect2(vRes.x - 80.f, 100.f));
	mFrameText->SetScale(Vect2(100.f, 30.f));
	mFrameText->SetColor(RGB(0, 255, 255));
	mFrameText->SetText(L"FPS");
	mFrameText->SetFontSize(24.f);
	CreateObject(mFrameText, GROUP_TYPE::UI);


	CBtnUI* pSettingBtn = new CBtnUI;
	pSettingBtn->SetScale(Vect2(50.f, 50.f));
	pSettingBtn->SetPos(Vect2(vRes.x - 50.f, 50.f));
	pSettingBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Button_2", L"texture\\ui\\button\\2.bmp"));
	pSettingBtn->SetClickedCallBack(mpSettinUI, OBJECT_FUNC(&SettingUI::Show));

	CImageUI* pImage = new CImageUI;
	pImage->SetPos(Vect2(0.f, -5.f));
	pImage->SetScale(pSettingBtn->GetScale() * 0.6f);
	pImage->SetTexture(CResMgr::GetI()->LoadTexture(L"Setting_Icon", L"texture\\ui\\icon\\setting.bmp"));
	pImage->SetRaycastTarget(false);
	pSettingBtn->AddChild(pImage);
	mpSettingBtn = pSettingBtn;
	CreateObject(mpSettingBtn, GROUP_TYPE::UI);


	CloseSettingUI();
	CloseGameOverUI();
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


void GUIMgr::SetFrameText(UINT frame)
{
	mFrameText->SetText(std::to_wstring(frame) + L" FPS");
}
