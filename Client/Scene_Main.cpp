#include "pch.h"
#include "Scene_Main.h"

// Include UI
#include "CBtnUI.h"
#include "CPanelUI.h"
#include "CResMgr.h"

#include "CCore.h"

void ChangeSceneStart(DWORD_PTR, DWORD_PTR);
void ChangeSceneTool(DWORD_PTR, DWORD_PTR);





Scene_Main::Scene_Main()
{
}


Scene_Main::~Scene_Main()
{
}


void Scene_Main::Update()
{
}


void Scene_Main::Enter()
{
	Vect2 vRes = CCore::GetI()->GetResolution();
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vect2(400.f, 800.f));
	pPanelUI->SetPos(Vect2(vRes.x * 0.5f, vRes.y * 0.5f));
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vect2(200.f, 50.f));
	pGameStartBtn->SetPos(Vect2(0.f,-100.f));
	pGameStartBtn->SetText(L"게임 시작");
	pGameStartBtn->SetContentOffset(Vect2(-40.f, -10.f));

	pGameStartBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pGameStartBtn->SetClickedCallBack(&ChangeSceneStart, 0, 0);
	pPanelUI->AddChild(pGameStartBtn);

	CBtnUI* pToolBtn = new CBtnUI;
	pToolBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pToolBtn->SetText(L"제작 모드");
	pToolBtn->SetContentOffset(Vect2(-40.f, -10.f));
	pToolBtn->SetScale(Vect2(200.f, 50.f));
	pToolBtn->SetClickedCallBack(&ChangeSceneTool, 0, 0);
	pToolBtn->SetPos(Vect2(0.f,0.f));
	pPanelUI->AddChild(pToolBtn);
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


