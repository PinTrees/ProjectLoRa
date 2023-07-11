#include "pch.h"
#include "Scene_Main.h"

// Include UI
#include "CBtnUI.h"


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
	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vec2(100.f, 50.f));
	pGameStartBtn->SetPos(Vec2(550.f, 350.f));
	//pGameStartBtn->SetText(L"게임 시작");
	pGameStartBtn->SetContentOffset(Vec2(20.f, 15.f));
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


