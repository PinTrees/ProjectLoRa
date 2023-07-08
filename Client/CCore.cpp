#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"

#include "CResMgr.h"
#include "CTexture.h"
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

	// 해상도에 맞게 윈도우 크기 조정하기
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// 메뉴바 생성
	mhMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	mhDC = GetDC(mhWnd);

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	mpMemTex = CResMgr::GetI()->CreateTexture(L"BackBuffer", (UINT)mPtResolution.x, (UINT)mPtResolution.y);

	// 자주사용할팬 브러쉬 생성
	CreateBrushPen();
	// manager 초기화
	CPathMgr::GetI()->Init();
	CTimeMgr::GetI()->Init();
	CKeyMgr::GetI()->Init();
	CCamera::GetI()->Init();
	CSceneMgr::GetI()->Init();
	return S_OK;
}

void CCore::Run()
{
	//manager update
	CTimeMgr::GetI()->Update();
	CKeyMgr::GetI()->Update();
	CCamera::GetI()->Update();
	//	============
	//	Scene Update
	//	============
	CSceneMgr::GetI()->Update();

	///충돌체크
	CCollisionMgr::GetI()->Update();

	// UI 이벤트 체크
	CUIMgr::GetI()->Update();

	//	========
	//	Rendering
	//	========
	//	화면 Clear
	//	========
	Clear();

	CSceneMgr::GetI()->Render(mpMemTex->GetDC());
	CCamera::GetI()->Render(mpMemTex->GetDC());


	BitBlt(mhDC, 0, 0, mPtResolution.x, mPtResolution.y
		, mpMemTex->GetDC(), 0, 0, SRCCOPY);


	CTimeMgr::GetI()->Render();


	//	============
	//	이벤트 지연처리
	//	============

	CEventMgr::GetI()->Update();
}

void CCore::Clear()
{
	SelectGDI gdi(mpMemTex->GetDC(), BRUSH_TYPE::BLACK);


	Rectangle(mpMemTex->GetDC(), -1, -1, mPtResolution.x + 1, mPtResolution.y + 1);
}

//
void CCore::CreateBrushPen()
{

	// hollow brush
	mArrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	mArrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red blue green pen
	mArrPen[(UINT)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	mArrPen[(UINT)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	mArrPen[(UINT)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	// 툴 Scene 에서 사용할 메뉴를 붙인다.
	SetMenu(mhWnd, mhMenu);
	ChangeWindowSize(GetResolution(),true);
}

void CCore::DivideMenu()
{
	SetMenu(mhWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{

	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(mhWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}



