#include "pch.h"
#include "Scene_Main.h"

// Include UI
#include "CBtnUI.h"
#include "CResMgr.h"

#include "CCore.h"

void ChangeSceneStart(DWORD_PTR, DWORD_PTR);




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

	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vect2(200.f, 50.f));
	pGameStartBtn->SetPos(vRes * 0.5f);
	pGameStartBtn->SetText(L"게임 시작");
	pGameStartBtn->SetContentOffset(Vect2(-40.f, -10.f));

	pGameStartBtn->SetTextrue(CResMgr::GetI()->LoadTexture(L"UI_Btn_1", L"texture\\ui\\button_1.bmp"));
	pGameStartBtn->SetClickedCallBack(&ChangeSceneStart, 0, 0);

	AddObject(pGameStartBtn, GROUP_TYPE::UI);
}


void Scene_Main::Exit()
{
}

void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}


