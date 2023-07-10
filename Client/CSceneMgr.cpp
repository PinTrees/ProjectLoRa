#include "pch.h"
#include "CSceneMgr.h"

// Include Scene
#include "CScene_start.h"
#include "CScene_Tool.h"
#include "Scene_Main.h"

// System Manager Header
#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CObject.h"


CSceneMgr::CSceneMgr()
	:m_arrScene{}
	, m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	// ¾À ÀüºÎ »èÁ¦
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}


void CSceneMgr::Init()
{
	// ¾À »ý¼º
	m_arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new Scene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::MAIN] = new Scene_Main;
	m_arrScene[(UINT)SCENE_TYPE::MAIN]->SetName(L"Main Scene");

	//ÇöÀç ¾À ÁöÁ¤
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::MAIN];
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	if (!CTimeMgr::GetI()->IsPlay())
	{
		vector<CObject*> arrUI = m_pCurScene->GetGroupObject(GROUP_TYPE::UI);
		for (int i = 0; i < arrUI.size(); ++i)
		{
			arrUI[i]->Update();
		}
		return;
	}

	m_pCurScene->Update();
}


void CSceneMgr::FinalUpdate()
{
	if (!CTimeMgr::GetI()->IsPlay())
	{
		vector<CObject*> arrUI = m_pCurScene->GetGroupObject(GROUP_TYPE::UI);
		for (int i = 0; i < arrUI.size(); ++i)
		{
			arrUI[i]->FinalUpdate();
		}
		return;
	}

	m_pCurScene->FinalUpdate();
}


void CSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);

}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}


