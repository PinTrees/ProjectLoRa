#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "UIMgr.h"
#include "CResMgr.h"
<<<<<<< Updated upstream
=======
#include "LevelupUIMgr.h"
>>>>>>> Stashed changes

#include "CCamera.h"
#include "CTexture.h"

#include "Random.h"

#include "SelectGDI.h"
#include "resource.h"

CCore::CCore()
	:mhWnd(0)
	, mPtResolution{}
	, mhDC(0)
	, mArrBrush{}
	, mArrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(mhWnd, mhDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(mArrPen[i]);
	}

	DestroyMenu(mhMenu); 
}
int CCore::Initialize(HWND _hWnd, POINT _ptResolution)
{
	mhWnd = _hWnd;
	mPtResolution = _ptResolution;

	// =================================
	// Window Resolution Size Initialize
	// =================================
<<<<<<< Updated upstream
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);	// menubar height size not include
=======
	ChangeWindowSize(Vect2((float)_ptResolution.x, (float)_ptResolution.y), false);	// menubar height size not include
>>>>>>> Stashed changes

	// Menu bar Create from ID;
	mhMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDR_MENU1));

	// ============================
	// Double Buffer DC and Texture
	// ============================
	mhDC = GetDC(mhWnd);
	mpMemTex = CResMgr::GetI()->CreateTexture(L"BackBuffer", (UINT)mPtResolution.x, (UINT)mPtResolution.y);
<<<<<<< Updated upstream
	SetBkMode(mpMemTex->GetDC(), TRANSPARENT);
=======
>>>>>>> Stashed changes
	CreateBrushPen();
	

	// ========================
	// Manager Initialize Block
	// ========================
	CPathMgr::GetI()->Init();
	CTimeMgr::GetI()->Init();
	CKeyMgr::GetI()->Init();
	CCamera::GetI()->Init();
	CSceneMgr::GetI()->Init();
	CRandom::GetI()->Init();
<<<<<<< Updated upstream
=======
	LevelupUIMgr::GetI()->Init();
>>>>>>> Stashed changes

	return S_OK;
}


void CCore::Run()
{
	// ====================
	// Manager Update Block
	// ====================
	CTimeMgr::GetI()->Update();
	CKeyMgr::GetI()->Update();
	CCamera::GetI()->Update();
<<<<<<< Updated upstream

	// ==================
	// Scene Update Block
	// ==================
	CSceneMgr::GetI()->Update();
=======

	// UI Update
	CUIMgr::GetI()->Update();


	// ==================
	// Scene Update Block
	// ==================
	if(CTimeMgr::GetI()->IsPlay())
	{
		CSceneMgr::GetI()->Update();
	}
	CSceneMgr::GetI()->FinalUpdate();
>>>>>>> Stashed changes


	// ======================
	// Collision Update Block
	// ======================
<<<<<<< Updated upstream
	CCollisionMgr::GetI()->Update();
	CUIMgr::GetI()->Update();

=======
	if (CTimeMgr::GetI()->IsPlay())
	{
		CCollisionMgr::GetI()->Update();
	}
	
>>>>>>> Stashed changes

	// ===============
	// Rendering Block
	// ===============
	Clear();

	// Scene Render
	CSceneMgr::GetI()->Render(mpMemTex->GetDC());
	CCamera::GetI()->Render(mpMemTex->GetDC());

	// Final DC Render
	BitBlt(mhDC
		, 0, 0
		, mPtResolution.x
		, mPtResolution.y
		, mpMemTex->GetDC()
		, 0, 0
		, SRCCOPY);

	CTimeMgr::GetI()->Render();


	// =================
	// Event Delay Block
	// =================
	CEventMgr::GetI()->Update();
}


void CCore::Clear()
{
	SelectGDI gdi(mpMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(mpMemTex->GetDC(), -1, -1, mPtResolution.x + 1, mPtResolution.y + 1);
}


void CCore::CreateBrushPen()
{
	mArrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	mArrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	mArrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);


	mArrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	mArrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	mArrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::SetActiveMenu(bool active)
{
	SetMenu(mhWnd, active ? mhMenu : nullptr);
	ChangeWindowSize(GetResolution(), active);
}


<<<<<<< Updated upstream
void CCore::ChangeWindowSize(Vec2 vResoulution, bool menuActive)
{
	RECT rt = { 0,0,vResoulution.x,vResoulution.y };
=======
void CCore::ChangeWindowSize(Vect2 vResoulution, bool menuActive)
{
	RECT rt = { 0,0, (LONG)vResoulution.x, (LONG)vResoulution.y };
>>>>>>> Stashed changes
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, menuActive);	// menubar height size not include
	SetWindowPos(mhWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}


