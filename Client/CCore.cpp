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

	// �ػ󵵿� �°� ������ ũ�� �����ϱ�
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴��� ����
	mhMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	mhDC = GetDC(mhWnd);

	// ���� ���۸� �뵵�� �ؽ��� ������ �����.
	mpMemTex = CResMgr::GetI()->CreateTexture(L"BackBuffer", (UINT)mPtResolution.x, (UINT)mPtResolution.y);

	// ���ֻ������ �귯�� ����
	CreateBrushPen();
	// manager �ʱ�ȭ
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

	///�浹üũ
	CCollisionMgr::GetI()->Update();

	// UI �̺�Ʈ üũ
	CUIMgr::GetI()->Update();

	//	========
	//	Rendering
	//	========
	//	ȭ�� Clear
	//	========
	Clear();

	CSceneMgr::GetI()->Render(mpMemTex->GetDC());
	CCamera::GetI()->Render(mpMemTex->GetDC());


	BitBlt(mhDC, 0, 0, mPtResolution.x, mPtResolution.y
		, mpMemTex->GetDC(), 0, 0, SRCCOPY);


	CTimeMgr::GetI()->Render();


	//	============
	//	�̺�Ʈ ����ó��
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
	// �� Scene ���� ����� �޴��� ���δ�.
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



