#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

CCore::CCore()
	:mhWnd(0)
	,mPtResolution{}
	,mhDC(0)
	,mhBit(0)
	,mMemDC(0)
{

}
CCore::~CCore()
{
	ReleaseDC(mhWnd, mhDC);

	DeleteDC(mMemDC);
	DeleteObject(mhBit);
}
int CCore::Initialize(HWND _hWnd, POINT _ptResolution)
{

	mhWnd = _hWnd;
	mPtResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정하기
	RECT rt = { 0,0,_ptResolution.x,_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(mhWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	mhDC = GetDC(mhWnd);

	// 이중 버퍼링 비트맵과 DC 생성
	mhBit = CreateCompatibleBitmap(mhDC, mPtResolution.x, mPtResolution.y);
	mMemDC = CreateCompatibleDC(mhDC);
	HBITMAP hOldBit = (HBITMAP)SelectObject(mMemDC, mhBit);
	DeleteObject(hOldBit);

	// manager 초기화
	CPathMgr::GetI()->Init();
	CTimeMgr::GetI()->Init();
	CKeyMgr::GetI()->Init();
	CSceneMgr::GetI()->Init();
	return S_OK;
}

void CCore::Run()
{
	//manager update
	CTimeMgr::GetI()->Update();
	CKeyMgr::GetI()->Update();


	///씬 업데이트 후 memdc 클리어 하고나서 씬 랜더 실행후 bitblt 실행
	CSceneMgr::GetI()->Update();
	Rectangle(mMemDC, -1, -1, mPtResolution.x + 1, mPtResolution.y + 1);
	CSceneMgr::GetI()->Render(mMemDC);
	BitBlt(mhDC, 0, 0, mPtResolution.x, mPtResolution.y, mMemDC, 0, 0, SRCCOPY);

	CTimeMgr::GetI()->Render();

}


