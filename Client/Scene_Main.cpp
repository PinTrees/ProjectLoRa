#include "pch.h"
#include "Scene_Main.h"

// UI Header
#include "CBtnUI.h"
#include "CResMgr.h"
#include "CPanelUI.h"
#include "CColumn.h"
#include "CImageUI.h"
#include "CWrap.h"

// Core Manager Header
#include "UIMgr.h"

#include "CCore.h"


void ChangeSceneStart(DWORD_PTR, DWORD_PTR);
void ChangeSceneTool(DWORD_PTR, DWORD_PTR);



Scene_Main::Scene_Main()
{
}


Scene_Main::~Scene_Main()
{
}



void Scene_Main::Enter()
{
	Vect2 vRes = CCore::GetI()->GetResolution();
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vect2(400.f, 400.f));
	pPanelUI->SetPos(Vect2(vRes.x * 0.5f, vRes.y * 0.5f));
	pPanelUI->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CColumn* pCol = new CColumn;
	pCol->SetPos(Vect2::zero);
	pCol->SetScale(Vect2(400.f, 700.f));
	pCol->SetSpacing(36.f);
	pPanelUI->AddChild(pCol);

	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vect2(200.f, 50.f));
	pGameStartBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pGameStartBtn->SetText(L"게임 시작");
	pGameStartBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pGameStartBtn->SetClickedCallBack(&ChangeSceneStart, 0, 0);
	pCol->AddChild(pGameStartBtn);

	CBtnUI* pToolBtn = new CBtnUI;
	pToolBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pToolBtn->SetScale(Vect2(200.f, 50.f));
	pToolBtn->SetText(L"제작 모드");
	pToolBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pToolBtn->SetClickedCallBack(&ChangeSceneTool, 0, 0);
	pCol->AddChild(pToolBtn);

	CBtnUI* pDictBtn = new CBtnUI;
	pDictBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pDictBtn->SetScale(Vect2(200.f, 50.f));
	pDictBtn->SetText(L"아이템 도감");
	pDictBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pDictBtn->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Main::OpenItemDataUI);
	pCol->AddChild(pDictBtn);
}


void Scene_Main::Update()
{
	CScene::Update();
}


void Scene_Main::Exit()
{
	DeleteAll();
}



void Scene_Main::OpenItemDataUI()
{
	Vect2 vRes = CCore::GetI()->GetResolution();

	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetFixedPos_xy(false);
	pPanelUI->SetScale(Vect2(800.f, 700.f));
	pPanelUI->SetPos(Vect2(vRes.x * 0.5f, vRes.y * 0.5f));
	pPanelUI->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));

	CWrap* pWrap = new CWrap;
	pWrap->SetPos(Vect2(0.f, 128.f));
	pWrap->SetScale(Vect2(800.f, 700.f));
	pPanelUI->AddChild(pWrap);

	for (int i = 0; i < 100; ++i)
	{
		CImageUI* pImg = new CImageUI;
		pImg->SetScale(Vect2(50.f, 50.f));
		pImg->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Item_" + std::to_wstring(i + 1), L"texture\\item\\26_" + std::to_wstring(i + 1) + L".bmp"));
		pWrap->AddChild(pImg);
	}

	CBtnUI* pCloseBtn = new CBtnUI;
	pCloseBtn->SetPos(Vect2(0.f, 300.f));
	pCloseBtn->SetScale(Vect2(200.f, 50.f));
	pCloseBtn->SetText(L"닫기");
	pCloseBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
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



void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}
void ChangeSceneTool(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TOOL);
}


