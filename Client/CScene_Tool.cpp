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
#include "CFont.h"
#include "CTexture.h"

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
	CCore::GetI()->SetActiveMenu(true);

	CreateTile(this, 5, 5);

	Vec2 vResolution = CCore::GetI()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x - 100.f, 0.f));
	pPanelUI->SetFont(CResMgr::GetI()->LoadFont(L"Ramche", L"font\\Ramche.ttf", 20, true));
	pPanelUI->SetContentOffset(Vec2(0.f, 50.f));
	pPanelUI->GetFont()->SetInnerColor(RGB(0, 255, 0));
	pPanelUI->GetFont()->SetOuterColor(RGB(255, 255, 0));
	pPanelUI->GetFont()->SetWord(L"테스트중입니다.");

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pBtnUI->SetTextrue(CResMgr::GetI()->LoadTexture(L"Gold", L"texture\\gold\\gold_1.bmp"));
	pBtnUI->SetChangeTex(CResMgr::GetI()->LoadTexture(L"Bronze", L"texture\\gold\\bronze_1.bmp"));
	pBtnUI->GetTextrue()->SetSize(Vec2(25.f, 25.f)); // 출력할 텍스쳐의 사이즈세팅

	// 함수를 인자로 넣을경우 명시적 주소표시 (전역함수만 생략 가능)
	pBtnUI->SetClickedCallBack(this, (SCENE_FUNC)&Scene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI); 
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CCamera::GetI()->SetLookAt(vResolution / 2.f);
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
		Vec2 vMousePos = MOUSE_POS;
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

	FileMgr::WirteByteFullPath(_fullPath, data.data(), data.size());
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
			
			pTile->SetScale(Vec2(TILE_SIZE_RENDER, TILE_SIZE_RENDER));
			pTile->SetPos(Vec2((float)(j * TILE_SIZE_RENDER), (float)i * TILE_SIZE_RENDER));
			pTile->SetTexture(pTileTex);

			pScene->AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}