#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"



CScene::CScene()
	:miTileX(0)
	, miTileY(0)
	, mpPlayer(nullptr)
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
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			Render_Tile(_dc);
			continue;
		}

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

void CScene::Render_Tile(HDC _dc)
{

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);


	Vec2 vCamLook = CCamera::GetI()->GetLookAt();
	Vec2 vResolution = CCore::GetI()->GetResolution();
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;
	int iLTIdx = (miTileX * iLTRow) + iLTCol;

	int iClientWidth = ((int)vResolution.x / iTileSize)+1;
	int iClientheight = ((int)vResolution.y/ iTileSize)+1;


	for (int iCurRow = iLTRow; iCurRow<(iLTRow+iClientheight);++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol+iClientWidth); ++iCurCol)
		{

			if (iCurCol < 0 || miTileX <= iCurCol
				|| iCurRow < 0 || miTileY <= iCurRow)
			{
				continue;
			}


			int iIdx = (miTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->Render(_dc);
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
