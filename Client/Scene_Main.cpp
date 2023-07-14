#include "pch.h"
#include "Scene_Main.h"

// UI Header
#include "CBtnUI.h"
#include "CResMgr.h"
#include "CPanelUI.h"
#include "CColumn.h"
#include "CImageUI.h"

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
}


void Scene_Main::Update()
{
	CScene::Update();
}


void Scene_Main::Exit()
{
	DeleteAll();
}


void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}
void ChangeSceneTool(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::TOOL);
}


