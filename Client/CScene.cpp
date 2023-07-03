#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"



CScene::CScene()
	:miTileX(0)
	, miTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < mArrObj[i].size(); j++)
		{
			//�׷캰 CObject ����
			delete mArrObj[i][j];
		}
	}
}

void CScene::AddObject(CObject* _pObj, GROUP_TYPE _eType)
{
	mArrObj[(UINT)_eType].push_back(_pObj);
}

void CScene::DeleteObject(CObject* _pObj, GROUP_TYPE _eType)
{
	//for (int i = 0; i < m_arrObj[(UINT)_eType].size(); ++i)
	//{
	//	if (_pObj == m_arrObj[(UINT)_eType][i])   
	//	{
	//		m_arrObj[(UINT)_eType].erase(m_arrObj[(UINT)_eType].begin() + i);
	//		
	//		break;
	//	}
	//}
}



void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size(); ++j)
		{
			if (!mArrObj[i][j]->IsDead())
			{
				mArrObj[i][j]->Update();
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < mArrObj[i].size(); ++j)
		{
			mArrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{

		vector<CObject*>::iterator iter = mArrObj[i].begin();
		for (; iter != mArrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				iter = mArrObj[i].erase(iter);
			}
		}
	}
}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(mArrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{

	DeleteGroup(GROUP_TYPE::TILE);
	miTileX = _iXCount;
	miTileY = _iYCount;


	CTexture* pTileTex = CResMgr::GetI()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;
	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// ������ ����

	UINT xCount =0;
	UINT yCount =0;
	// Ÿ�� ���μ��� ���� �ҷ�����
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// �ҷ��� ������ �°� emptyTile�� ����� �α�
	CreateTile(xCount, yCount);

	// ������� Ÿ�� ������ �ʿ��� ������ �ҷ����� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);

}
