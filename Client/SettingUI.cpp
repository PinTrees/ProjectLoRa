#include "pch.h"
#include "SettingUI.h"

#include "CResMgr.h"

#include "CCore.h"
#include "CImageUI.h"
#include "CBtnUI.h"
#include "CColumn.h"
#include "CRow.h"
#include "CWrap.h"
#include "TextUI.h"

#include "GUIMgr.h"
#include "SettingMgr.h"

#include "CSystemMgr.h"

#include "CScrollView.h"



SettingUI::SettingUI()
	: mJPSBtn(nullptr)
	, mAstarBtn(nullptr)
	, mDebugBtn(nullptr)
	, mDebugCheckIcon(nullptr)
{
	SetFixedPos(false);
	SetScale(Vect2(500.f, 500.f));
	SetTexture(CResMgr::GetI()->LoadSprite(L"Panel_1", L"texture\\ui\\panel_1.png"));

	CBtnUI* pCloseBtn = new CBtnUI;
	pCloseBtn->SetScale(Vect2(50.f, 50.f));
	pCloseBtn->SetPos(Vect2(GetScale().x * 0.5f - 50.f, GetScale().y * -0.5f + 50.f));
	pCloseBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_1", L"texture\\ui\\button\\1.bmp"));
	pCloseBtn->SetClickedCallBack(this, OBJECT_FUNC(&SettingUI::Close));
	AddChild(pCloseBtn);

	CImageUI* pIcon = new CImageUI;
	pIcon->SetPos(Vect2::zero);
	pIcon->SetScale(pCloseBtn->GetScale() * 0.6f);
	pIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Close", L"texture\\ui\\icon\\close.bmp"));
	pIcon->SetRaycastTarget(false);
	pCloseBtn->AddChild(pIcon);

	CScrollView* pScroll = new CScrollView;
	pScroll->SetPos(Vect2(0.f, 25.f));
	pScroll->SetScale(Vect2(400.f, 350.f));
	AddChild(pScroll);

	CColumn* pColumn = new CColumn;
	pColumn->SetScale(Vect2(450.f, 500.f));
	pScroll->AddChild(pColumn);

	TextUI* pPathSetting = new TextUI;
	pPathSetting->SetScale(Vect2(0.f, 50.f));
	pPathSetting->SetFontSize(28.f);
	pPathSetting->SetColor(RGB(255, 255, 255));
	pPathSetting->SetText(L"몬스터 길찾기 알고리즘");
	pColumn->AddChild(pPathSetting);

	CRow* pRow = new CRow;
	pRow->SetScale(Vect2(500.f, 60.f));
	pRow->SetSpacing(16.f);
	pColumn->AddChild(pRow);

	mAstarBtn = new CBtnUI;
	mAstarBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_3", L"texture\\ui\\button\\3.bmp"));
	mAstarBtn->SetScale(Vect2(150.f, 45.f));
	mAstarBtn->SetText(L"Astar");
	mAstarBtn->SetClickedCallBack(this, OBJECT_FUNC_P(&SettingUI::SetFindPath), (DWORD_PTR)FIND_PATH_TYPE::ASTAR);
	pRow->AddChild(mAstarBtn);

	mJPSBtn = new CBtnUI;
	mJPSBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_3", L"texture\\ui\\button\\3.bmp"));
	mJPSBtn->SetScale(Vect2(150.f, 45.f));
	mJPSBtn->SetText(L"JPS B");
	mJPSBtn->SetClickedCallBack(this, OBJECT_FUNC_P(&SettingUI::SetFindPath), (DWORD_PTR)FIND_PATH_TYPE::JPS_B);
	pRow->AddChild(mJPSBtn);

	// Debug UI
	TextUI* pDebugSetting = new TextUI;
	pDebugSetting->SetScale(Vect2(0.f, 50.f));
	pDebugSetting->SetFontSize(28.f);
	pDebugSetting->SetColor(RGB(255, 255, 255));
	pDebugSetting->SetText(L"개발자 설정");
	pColumn->AddChild(pDebugSetting);

	CRow* pDebugRow = new CRow;
	pDebugRow->SetScale(Vect2(500.f, 60.f));
	pDebugRow->SetSpacing(16.f);
	pColumn->AddChild(pDebugRow);

	TextUI* pDebugText = new TextUI;
	pDebugText->SetScale(Vect2(150.f, 25.f));
	pDebugText->SetFontSize(24.f);
	pDebugText->SetColor(RGB(150, 150, 150));
	pDebugText->SetText(L"Debug Mode");
	pDebugRow->AddChild(pDebugText);

	mDebugBtn = new CBtnUI;
	mDebugBtn->SetScale(Vect2(30.f, 30.f));
	mDebugBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_1", L"texture\\ui\\button\\1.bmp"));
	mDebugBtn->SetClickedCallBack(this, OBJECT_FUNC(&SettingUI::SetDebugMode));
	pDebugRow->AddChild(mDebugBtn);

	mDebugCheckIcon = new CImageUI;
	mDebugCheckIcon->SetScale(Vect2(30.f, 30.f));
	mDebugCheckIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Check", L"texture\\ui\\icon\\check.bmp"));
	mDebugCheckIcon->SetRaycastTarget(false);
	mDebugBtn->AddChild(mDebugCheckIcon);

	// 데미지 텍스트 옵션 UI -------------------------------------------------------
	CRow* pDamageRow = new CRow;
	pDamageRow->SetScale(Vect2(500.f, 60.f));
	pDamageRow->SetSpacing(16.f);
	pColumn->AddChild(pDamageRow);

	TextUI* pDamageTitle = new TextUI;
	pDamageTitle->SetScale(Vect2(230.f, 25.f));
	pDamageTitle->SetFontSize(22.f);
	pDamageTitle->SetColor(RGB(255, 255, 255));
	pDamageTitle->SetText(L"데미지 텍스트 표시");
	pDamageRow->AddChild(pDamageTitle);

	mDamageTextBtn = new CBtnUI;
	mDamageTextBtn->SetScale(Vect2(30.f, 30.f));
	mDamageTextBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_1", L"texture\\ui\\button\\1.bmp"));
	mDamageTextBtn->SetClickedCallBack(this, OBJECT_FUNC(&SettingUI::SetDamageText));
	pDamageRow->AddChild(mDamageTextBtn);

	mDamageTextCheckIcon = new CImageUI;
	mDamageTextCheckIcon->SetScale(Vect2(30.f, 30.f));
	mDamageTextCheckIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Check", L"texture\\ui\\icon\\check.bmp"));
	mDamageTextCheckIcon->SetRaycastTarget(false);
	mDamageTextBtn->AddChild(mDamageTextCheckIcon);
}


SettingUI::~SettingUI()
{
}




void SettingUI::Close()
{
	GUIMgr::GetI()->CloseSettingUI();
}

// 추후 사용 - 다이얼로그 공통 인터페이스 
void SettingUI::Show()
{
	GUIMgr::GetI()->ShowSettingUI();
}


void SettingUI::Build()
{
	auto tCurFindPathType = SettingMgr::GetI()->GetFindPathType();

	/*if (tCurFindPathType == FIND_PATH_TYPE::ASTAR)
	{
		mJPSBtn->DeleteChild(mCurSelectIcon);
		mAstarBtn->AddChild(mCurSelectIcon);
	}
	else if (tCurFindPathType == FIND_PATH_TYPE::JPS_B)
	{
		mAstarBtn->DeleteChild(mCurSelectIcon);
		mJPSBtn->AddChild(mCurSelectIcon);
	}*/

	mDebugCheckIcon->SetVisible(DEBUG);
	mDamageTextCheckIcon->SetVisible(SettingMgr::GetI()->GetDamageTextActive());
}


void SettingUI::SetFindPath(DWORD_PTR param)
{
	SettingMgr::GetI()->SetFindPathType((FIND_PATH_TYPE)param);
	Build();
}

void SettingUI::SetDebugMode()
{
	CSystemMgr::GetI()->SetDebug(!DEBUG);
	Build();
}

void SettingUI::SetDamageText()
{
	SettingMgr::GetI()->SetDamageTextActive(!SettingMgr::GetI()->GetDamageTextActive());
	Build();
}
