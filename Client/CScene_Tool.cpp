#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"
#include "Tile.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "resource.h"

#include "UIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "FileMgr.h"
#include "CPathMgr.h"


// function header
void ChangeScene(DWORD_PTR, DWORD_PTR);
void CreateTile(Scene_Tool* pScene, UINT xCount, UINT yCount);


Scene_Tool::Scene_Tool()
	: mpUI(nullptr)
	, mTileX(1)
	, mTileY(1)
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::Enter()
{
	//CCore::GetI()->SetActiveMenu(true);

	//CreateTile(this, 5, 5);

	//Vect2 vResolution = CCore::GetI()->GetResolution();
	//CCamera::GetI()->SetLookAt(vResolution * 0.5f); //카메라 이동

	//CUI* pPanelUI = new CPanelUI;
	//pPanelUI->SetName(L"ParentUI");
	//pPanelUI->SetScale(Vect2(300.f, 150.f));
	//pPanelUI->SetPos(Vect2(vResolution.x - pPanelUI->GetScale().x - 100.f, 100.f));

	//CBtnUI* pBtnUI = new CBtnUI;
	//pBtnUI->SetName(L"ChildUI");
	//pBtnUI->SetScale(Vect2(100.f, 40.f));
	//pBtnUI->SetPos(Vect2(0.f, 0.f));

	//// 함수를 인자로 넣을경우 명시적 주소표시 (전역함수만 생략 가능)
	//pBtnUI->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Tool::SaveTileData);
	//pPanelUI->AddChild(pBtnUI); 
	//AddObject(pPanelUI, GROUP_TYPE::UI);

}

void Scene_Tool::Exit()
{
	CCore::GetI()->SetActiveMenu(false);
	DeleteAll();
}



void Scene_Tool::Update()
{
	CScene::Update();

	SetTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
	}
	if (KEY_TAP(KEY::CTRL))
	{
		//CUIMgr::GetI()->SetFocusedUI(mpUI);
		LoadTIleData();
	}
}

void Scene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vect2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetI()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE_RENDER;
		int iRow = (int)vMousePos.y / TILE_SIZE_RENDER;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((Tile*)vecTile[iIdx])->AddImgIdx();
	}
}



void Scene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetI()->GetMainHwnd();  
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
		
	wstring strTitleFolder = CPathMgr::GetI()->GetContentPath();
	strTitleFolder += L"database";

	ofn.lpstrInitialDir = strTitleFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal Dialog
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}



void Scene_Tool::LoadTIleData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetI()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTitleFolder = CPathMgr::GetI()->GetContentPath();
	strTitleFolder += L"database";

	ofn.lpstrInitialDir = strTitleFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal Dialog
	if (GetOpenFileName(&ofn))
	{
		wstring path = CPathMgr::GetI()->GetRelativePath(szName);
		LoadTile(path);
	}
}







void Scene_Tool::SaveTile(const wstring& _fullPath)
{
	vector<uint8_t> data;  // 바이트 배열을 저장할 벡터 생성

	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	// xCount와 yCount를 벡터에 추가
	data.insert(data.end(), reinterpret_cast<uint8_t*>(&xCount), reinterpret_cast<uint8_t*>(&xCount) + sizeof(UINT));
	data.insert(data.end(), reinterpret_cast<uint8_t*>(&yCount), reinterpret_cast<uint8_t*>(&yCount) + sizeof(UINT));

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		Tile* tile = dynamic_cast<Tile*>(vecTile[i]);
		if (tile) {
			// Tile 객체의 데이터를 벡터에 추가
			vector<uint8_t> tileData = tile->Save();
			data.insert(data.end(), tileData.begin(), tileData.end());
		}
	}

	FileMgr::WirteByteFullPath(_fullPath, data.data(), (int)data.size());
}

void Scene_Tool::LoadTile(const wstring& _fullPath)
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

	CreateTile(this, xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((Tile*)(vecTile[i]))->Load(pFile);
	}

	fclose(pFile);
}





void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}




// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetI()->GetCurScene();

			Scene_Tool* pToolScene = dynamic_cast<Scene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			CreateTile(pToolScene, iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}


void CreateTile(Scene_Tool* pScene, UINT xCount, UINT yCount)
{
	pScene->DeleteGroup(GROUP_TYPE::TILE);

	CTexture* pTileTex = CResMgr::GetI()->LoadTexture(L"TILE_1", L"texture\\tiles\\1.bmp");

	pScene->SetTileX(xCount);
	pScene->SetTileY(yCount);

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