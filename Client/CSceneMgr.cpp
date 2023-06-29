#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_start.h"


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
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_start;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_start;


	//ÇöÀç ¾À ÁöÁ¤
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
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
