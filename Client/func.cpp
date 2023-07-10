#include "pch.h"
#include "func.h"

// Include Manager
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CTexture.h"

#include "Tile.h"
#include "Background.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;

	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetI()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetI()->AddEvent(evn);
}


void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetI()->AddEvent(evn);
}


void ChangeAIState(AI* pAI, MONSTER_STATE nextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)pAI;
	evn.wParam = (DWORD_PTR)nextState;

	CEventMgr::GetI()->AddEvent(evn);
}


void CreateForce(tForce& force)
{
	CScene* pScene = CSceneMgr::GetI()->GetCurScene();
	pScene->AddForce(force);
}





Vect2 curvesCircle(Vect2 c1, float _radius, float _amount)
{
	float angle = _amount * 2 * PI;

	float x = c1.x + _radius * cos(angle);
	float y = c1.y + _radius * sin(angle);

	return Vect2(x, y);
}








void FlipImage(HDC hdc, int x, int y, int width, int height, HDC srcDC, int srcX, int srcY, int srcWidth, int srcHeight)
{
    // �ø��� �̹����� �׸� �޸� DC ����
    HDC flipDC = CreateCompatibleDC(hdc);
    HBITMAP flipBitmap = CreateCompatibleBitmap(hdc, width, height);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(flipDC, flipBitmap);

    // �̹����� �������� ������ ���� ��ȯ ��� ����
    XFORM transform;
    transform.eM11 = -1.0f;
    transform.eM12 = 0.0f;
    transform.eM21 = 0.0f;
    transform.eM22 = 1.0f;
    transform.eDx = srcWidth;
    transform.eDy = 0.0f;

    // ��ȯ ��� ����
    SetGraphicsMode(flipDC, GM_ADVANCED);
    SetWorldTransform(flipDC, &transform);

    // ���� �̹����� �ø��� �޸� DC�� �׸���
    BitBlt(flipDC, 0, 0, width, height, srcDC, srcX, srcY, SRCCOPY);

    // ��ȯ ��� �ʱ�ȭ
    ModifyWorldTransform(flipDC, nullptr, MWT_IDENTITY);
    SetWorldTransform(flipDC, nullptr);

    // �ø��� �̹����� ���
    TransparentBlt(hdc, x, y, width, height, flipDC, 0, 0, srcWidth, srcHeight, RGB(255, 0, 255));

    // �޸� ����
    SelectObject(flipDC, oldBitmap);
    DeleteObject(flipBitmap);
    DeleteDC(flipDC);
}










void LoadTile(CScene* pScene, const wstring& _fullPath)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _fullPath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);


	Background* pParallax = new Background();
	pParallax->CreateParallaxTexture(xCount * TILE_SIZE, yCount * TILE_SIZE);

	HDC dc = pParallax->GetParallaxDC();

	CreateTile(pScene, xCount, yCount);
	const vector<CObject*>& vecTile = pScene->GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		Tile* tile = (Tile*)(vecTile[i]);
		tile->Load(pFile);
		tile->Render(dc);
	}

	pScene->AddObject(pParallax, GROUP_TYPE::PARALLAX);
	pScene->DeleteGroup(GROUP_TYPE::TILE);

	fclose(pFile);
}

void CreateTile(CScene* pScene, UINT xCount, UINT yCount)
{
	pScene->DeleteGroup(GROUP_TYPE::TILE);

	CTexture* pTileTex = CResMgr::GetI()->LoadTexture(L"TILE_1", L"texture\\tiles\\1.bmp");

	for (UINT i = 0; i < yCount; ++i)
	{
		for (UINT j = 0; j < xCount; ++j)
		{
			Tile* pTile = new Tile();

			pTile->SetScale(Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER));
			pTile->SetPos(Vect2((float)(j * TILE_SIZE_RENDER), (float)i * TILE_SIZE_RENDER));
			pTile->SetTexture(pTileTex);

			pScene->AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}