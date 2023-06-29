#include "pch.h"
#include "CScene.h"
#include "CObject.h"

void CScene::AddObject(CObject* _pObj, GROUP_TYPE _eType)
{
	m_arrObj[(UINT)_eType].push_back(_pObj);
}

void CScene::DeleteObject(CObject* _pObj, GROUP_TYPE _eType)
{
	for (int i = 0; i < m_arrObj[(UINT)_eType].size(); ++i)
	{
		if (_pObj == m_arrObj[(UINT)_eType][i])
		{
			m_arrObj[(UINT)_eType].erase(m_arrObj[(UINT)_eType].begin() + i);
			break;
		}
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			//그룹별 CObject 삭제
			delete m_arrObj[i][j];
		}
	}
}
void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size();++j)
		{
			m_arrObj[i][j]->Update();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Render(_dc);
		}
	}
}
