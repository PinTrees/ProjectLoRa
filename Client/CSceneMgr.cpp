#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_start.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"

CSceneMgr::CSceneMgr()
	:m_arrScene{}
	, m_pCurScene(nullptr)
{
}
CSceneMgr::~CSceneMgr()
{
	// �� ���� ����
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
	// �� ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_start;


	//���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TOOL];
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
	
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


