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
#include "CSlider.h"
#include "CCore.h"


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
	pColumn->SetScale(Vect2(450.f, 650.f));
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
	CRow* pDebugRow = new CRow;
	pDebugRow->SetScale(Vect2(500.f, 60.f));
	pDebugRow->SetSpacing(16.f);
	pColumn->AddChild(pDebugRow);

	TextUI* pDebugText = new TextUI;
	pDebugText->SetScale(Vect2(230.f, 25.f));
	pDebugText->SetOutlineColor(RGB(255, 255, 255));
	pDebugText->SetOutlineWidth(2);
	pDebugText->SetFontSize(24.f);
	pDebugText->SetColor(RGB(0, 0, 0));
	pDebugText->SetText(L"개발자 설정 표시");
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
	pDamageTitle->SetOutlineColor(RGB(255, 255, 255));
	pDamageTitle->SetOutlineWidth(2);
	pDamageTitle->SetFontSize(24.f);
	pDamageTitle->SetColor(RGB(0, 0, 0));
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

	// 데미지 텍스트 옵션 UI -------------------------------------------------------
	CRow* pMonHpRow = new CRow;
	pMonHpRow->SetScale(Vect2(500.f, 60.f));
	pMonHpRow->SetSpacing(16.f);
	pColumn->AddChild(pMonHpRow);

	TextUI* pShowMonHpTitle = new TextUI;
	pShowMonHpTitle->SetScale(Vect2(230.f, 25.f));
	pShowMonHpTitle->SetOutlineColor(RGB(255, 255, 255));
	pShowMonHpTitle->SetOutlineWidth(2);
	pShowMonHpTitle->SetFontSize(24.f);
	pShowMonHpTitle->SetColor(RGB(0, 0, 0));
	pShowMonHpTitle->SetText(L"몬스터 체력바 표시");
	pMonHpRow->AddChild(pShowMonHpTitle);

	mShowHpBarBtn = new CBtnUI;
	mShowHpBarBtn->SetScale(Vect2(30.f, 30.f));
	mShowHpBarBtn->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_1", L"texture\\ui\\button\\1.bmp"));
	mShowHpBarBtn->SetClickedCallBack(this, OBJECT_FUNC(&SettingUI::SetShowMonsterHpBar));
	pMonHpRow->AddChild(mShowHpBarBtn);

	mShowHpBarTextCheckIcon = new CImageUI;
	mShowHpBarTextCheckIcon->SetScale(Vect2(30.f, 30.f));
	mShowHpBarTextCheckIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Check", L"texture\\ui\\icon\\check.bmp"));
	mShowHpBarTextCheckIcon->SetRaycastTarget(false);
	mShowHpBarBtn->AddChild(mShowHpBarTextCheckIcon);

	// 사운드 슬라이더 UI ---------------------------------------
	TextUI* pSoundTitle = new TextUI;
	pSoundTitle->SetScale(Vect2(0.f, 100.f));
	pSoundTitle->SetFontSize(28.f);
	pSoundTitle->SetColor(RGB(255, 255, 255));
	pSoundTitle->SetText(L"사운드");
	pColumn->AddChild(pSoundTitle);

	CRow* pVolRow = new CRow;
	pVolRow->SetScale(Vect2(500.f, 60.f));
	pVolRow->SetSpacing(16.f);
	pColumn->AddChild(pVolRow);

	CImageUI* pSoundIcon = new CImageUI;
	pSoundIcon->SetScale(Vect2(38.f, 38.f));
	pSoundIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Sound", L"texture\\ui\\icon\\sound.bmp"));
	pVolRow->AddChild(pSoundIcon);

	mSoundSlider = new CSlider;
	mSoundSlider->SetScale(Vect2(200.f, 60.f));
	mSoundSlider->SetChangeValueFunc(this, (SLIDER_OBJ)(&SettingUI::ChangeSoundSliderValue));
	pVolRow->AddChild(mSoundSlider);

	mVolumText = new TextUI;
	mVolumText->SetScale(Vect2(50.f, 25.f));
	mVolumText->SetFontSize(22.f);
	mVolumText->SetColor(RGB(255, 255, 255));
	mVolumText->SetText(L"100");
	pVolRow->AddChild(mVolumText);

	// BGM 볼륨 슬라이더 ------------------------------------
	TextUI* pBgmSoundTitle = new TextUI;
	pBgmSoundTitle->SetScale(Vect2(0.f, 100.f));
	pBgmSoundTitle->SetFontSize(28.f);
	pBgmSoundTitle->SetColor(RGB(255, 255, 255));
	pBgmSoundTitle->SetText(L"BGM 사운드");
	pColumn->AddChild(pBgmSoundTitle);

	CRow* pBGMVolRow = new CRow;
	pBGMVolRow->SetScale(Vect2(500.f, 60.f));
	pBGMVolRow->SetSpacing(16.f);
	pColumn->AddChild(pBGMVolRow);

	CImageUI* pBGMSoundIcon = new CImageUI;
	pBGMSoundIcon->SetScale(Vect2(38.f, 38.f));
	pBGMSoundIcon->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Sound", L"texture\\ui\\icon\\sound.bmp"));
	pBGMVolRow->AddChild(pBGMSoundIcon);

	mBgmSoundSlider = new CSlider;
	mBgmSoundSlider->SetScale(Vect2(200.f, 60.f));
	mBgmSoundSlider->SetChangeValueFunc(this, (SLIDER_OBJ)(&SettingUI::ChangeBGMSoundSliderValue));
	pBGMVolRow->AddChild(mBgmSoundSlider);

	mBgmVolumText = new TextUI;
	mBgmVolumText->SetScale(Vect2(50.f, 25.f));
	mBgmVolumText->SetFontSize(22.f);
	mBgmVolumText->SetColor(RGB(255, 255, 255));
	mBgmVolumText->SetText(L"100");
	pBGMVolRow->AddChild(mBgmVolumText);


	TextUI* pResTitle = new TextUI;
	pResTitle->SetScale(Vect2(0.f, 100.f));
	pResTitle->SetFontSize(28.f);
	pResTitle->SetColor(RGB(255, 255, 255));
	pResTitle->SetText(L"해상도");
	pColumn->AddChild(pResTitle);

	wstring resTex[3] =
	{
		L"1280 X 720",
		L"1920 X 1080",
		L"전체화면",
	};

	for (int i = 0; i < 3; ++i)
	{
		CRow* pResRow = new CRow;
		pResRow->SetScale(Vect2(500.f, 38.f));
		pResRow->SetSpacing(16.f);
		pColumn->AddChild(pResRow);

		TextUI* pResText = new TextUI;
		pResText->SetScale(Vect2(230.f, 25.f));
		pResText->SetOutlineColor(RGB(255, 255, 255));
		pResText->SetOutlineWidth(2);
		pResText->SetFontSize(24.f);
		pResText->SetColor(RGB(0, 0, 0));
		pResText->SetText(resTex[i]);
		pResRow->AddChild(pResText);

		mResBtn[i] = new CBtnUI;
		mResBtn[i]->SetScale(Vect2(30.f, 30.f));
		mResBtn[i]->SetTexture(CResMgr::GetI()->LoadTexture(L"Btn_1", L"texture\\ui\\button\\1.bmp"));
		mResBtn[i]->SetClickedCallBack(this, OBJECT_FUNC_P(&SettingUI::SetResolution), (DWORD_PTR)i);
		pResRow->AddChild(mResBtn[i]);

		mResCheckIcon[i] = new CImageUI;
		mResCheckIcon[i]->SetScale(Vect2(30.f, 30.f));
		mResCheckIcon[i]->SetTexture(CResMgr::GetI()->LoadTexture(L"Icon_Check", L"texture\\ui\\icon\\check.bmp"));
		mResCheckIcon[i]->SetRaycastTarget(false);
		mResCheckIcon[i]->SetVisible(i == 0);

		mResBtn[i]->AddChild(mResCheckIcon[i]);
	}
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
	mShowHpBarTextCheckIcon->SetVisible(SettingMgr::GetI()->GetMonsterHpbarActive());
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

void SettingUI::SetShowMonsterHpBar()
{
	SettingMgr::GetI()->SetMonsterHpbarActive(!SettingMgr::GetI()->GetMonsterHpbarActive());
	Build();
}

void SettingUI::SetResolution(int i)
{
	//CCore::GetI()->ChangeWindowSize(Vect2(1080, 1080), false);
}


void SettingUI::ChangeSoundSliderValue(int val)
{
	mVolumText->SetText(std::to_wstring(val));
	SettingMgr::GetI()->SetVolume(val);
}

void SettingUI::ChangeBGMSoundSliderValue(int val)
{
	mBgmVolumText->SetText(std::to_wstring(val));
	SettingMgr::GetI()->SetBGMVolume(val);
}
