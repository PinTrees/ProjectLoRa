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
#include "CWrap.h"
#include "CImageUI.h"

#include "FileMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"

// Tool_Scene Mgr
#include "ToolMgr.h"

// function header
void ChangeScene(DWORD_PTR, DWORD_PTR);
void SelectTile(DWORD_PTR, DWORD_PTR);
void CreateTile(Scene_Tool* pScene, UINT xCount, UINT yCount);


Scene_Tool::Scene_Tool()
	: mTileX(1)
	, mTileY(1)
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::Enter()
{
	CCore::GetI()->SetActiveMenu(true);

	LoadTile(L"database\\map_1.tile");

	Vect2 vResolution = CCore::GetI()->GetResolution();

	// TileEditUI
	CUI* pEditPanel = new CPanelUI;
	pEditPanel->SetName(L"EditPanel");
	pEditPanel->SetScale(Vect2(vResolution.x * 0.4f, vResolution.y));
	pEditPanel->SetPos(Vect2(vResolution.x - (pEditPanel->GetScale().x*0.5f), vResolution.y*0.5f));
	pEditPanel->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_panel_1", L"texture\\ui\\panel_1.bmp"));
	((CPanelUI*)pEditPanel)->SetFixedPos(false);

	CUI* pEditWrap = new CWrap;
	pEditWrap->SetScale(Vect2(pEditPanel->GetScale()));
	pEditWrap->SetPos(Vect2(0.f, 130.f));
	pEditPanel->AddChild(pEditWrap);

	/// *** 버튼을 상속받는 CTileUI새로 만들어야함
	for (int i = 0; i < 30; ++i)
	{
		CUI* pImg = new CBtnUI;
		pImg->SetScale(Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER));
		pImg->SetTexture(CResMgr::GetI()->LoadTexture(L"UI_Tile_" + std::to_wstring(i + 1)
			,L"texture\\item\\26_" + std::to_wstring(i + 1) + L".bmp"));
		pEditWrap->AddChild(pImg);
	}

	CreateObject(pEditPanel, GROUP_TYPE::UI);





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
	// 마우스클릭된 좌표위에 UI가있을경우 UI클릭만하고 타일은 클릭 예외처리
	if (CUIMgr::GetI()->IsMouseOnUI())
	{
		CUIMgr::GetI()->SetMouseOnUI(false);
		return;
	}

	if (KEY_TAP(KEY::LBTN))
	{
		//현재 마우스 좌표 가져옴
		Vect2 vMousePos = MOUSE_POS;
		// 카메라에서 실제좌표로 변경
		vMousePos = CCamera::GetI()->GetRealPos(vMousePos);

	
		int iCol = (int)vMousePos.x / TILE_SIZE_RENDER;
		int iRow = (int)vMousePos.y / TILE_SIZE_RENDER;

		if (vMousePos.x < 0.f || static_cast<int>(mTileX) <= iCol || vMousePos.y < 0.f || static_cast<int>(mTileY) <= iRow)
		{
			return;
		}

		//타일 인덱스
		UINT iIdx = iRow * mTileX + iCol;

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

	if (nullptr == pFile)
	{
		CreateTile(this, 5, 5);
		return;
	}

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


void SelectTile(DWORD_PTR, DWORD_PTR)
{
	
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



void Scene_Tool::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			render_tile(_dc);
			continue;
		}

		//Render Background
		if ((UINT)GROUP_TYPE::PARALLAX == i)
		{
			continue;
		}

		vector<CObject*>::iterator iter = mArrObj[i].begin();

		for (; iter != mArrObj[i].end();)
		{
			// Render Object
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				++iter;
			}
			// Delete Object
			else
			{
				(*iter)->OnDestroy();
				iter = mArrObj[i].erase(iter);
			}
		}
	}
}


void Scene_Tool::render_tile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vect2 vCamLook = CCamera::GetI()->GetLookAt();
	Vect2 vResolution = CCore::GetI()->GetResolution();
	Vect2	vLeftTop = vCamLook - vResolution * 0.5f;

	int iTileSize = TILE_SIZE_RENDER;

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	int iLTIdx = (mTileX * iLTRow) + iLTCol;

	int iClientWidth = ((int)vResolution.x / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;


	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			if (iCurCol < 0 || mTileX <= (UINT)iCurCol
				|| iCurRow < 0 || mTileY <= (UINT)iCurRow)
			{
				continue;
			}
			int iIdx = (mTileX * iCurRow) + iCurCol;
			((Tile*)vecTile[iIdx])->Render(_dc, true);
		}
	}
}