#include "pch.h"
#include "CScene_Menu.h"
#include "CBtnUI.h"
#include "func.h"

CScene_Menu::CScene_Menu()
{
}

CScene_Menu::~CScene_Menu()
{
}

void CScene_Menu::Update()
{

}

void ChangeSceneStart(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

void CScene_Menu::Enter()
{
	CBtnUI* pGameStartBtn = new CBtnUI;
	pGameStartBtn->SetScale(Vec2(100.f, 50.f));
	pGameStartBtn->SetPos(Vec2(550.f, 350.f));
	pGameStartBtn->SetText(L"게임 시작");
	pGameStartBtn->SetContentOffset(Vec2(20.f, 15.f));
	pGameStartBtn->SetClickedCallBack(&ChangeSceneStart, 0, 0);
	AddObject(pGameStartBtn, GROUP_TYPE::UI);
}

void CScene_Menu::Exit()
{
	DeleteAll();
}