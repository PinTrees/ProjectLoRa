#include "pch.h"
#include "GUIMgr.h"

#include "CTimeMgr.h"

#include "SettingUI.h"

#include "CResMgr.h"

#include "CCore.h"
#include "CImageUI.h"
#include "CBtnUI.h"
#include "TextUI.h"


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
	mpBackground->SetAlpha(150);
	mpBackground->SetColor(RGB(0, 0, 0));
	CreateObject(mpBackground, GROUP_TYPE::UI);

	mpSettinUI = new SettingUI;
	mpSettinUI->SetPos(vRes * 0.5f);
	CreateObject(mpSettinUI, GROUP_TYPE::UI);

	mFrameText = new TextUI;
	mFrameText->SetPos(Vect2(vRes.x - 80.f, 100.f));
	mFrameText->SetScale(Vect2(100.f, 30.f));
	mFrameText->SetColor(RGB(0, 255, 255));
	mFrameText->SetText(L"FPS");
	mFrameText->SetFontSize(24.f);
	CreateObject(mFrameText, GROUP_TYPE::UI);

	CloseSettingUI();
}

void GUIMgr::ShowSettingUI()
{
	CTimeMgr::GetI()->Stop();
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

void GUIMgr::SetFrameText(UINT frame)
{
	mFrameText->SetText(std::to_wstring(frame) + L" FPS");
}
