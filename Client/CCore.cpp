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

	// �ػ󵵿� �°� ������ ũ�� �����ϱ�
	RECT rt = { 0,0,_ptResolution.x,_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(mhWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	mhDC = GetDC(mhWnd);

	// ���� ���۸� ��Ʈ�ʰ� DC ����
	mhBit = CreateCompatibleBitmap(mhDC, mPtResolution.x, mPtResolution.y);
	mMemDC = CreateCompatibleDC(mhDC);
	HBITMAP hOldBit = (HBITMAP)SelectObject(mMemDC, mhBit);
	DeleteObject(hOldBit);

	// manager �ʱ�ȭ
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


	///�� ������Ʈ �� memdc Ŭ���� �ϰ��� �� ���� ������ bitblt ����
	CSceneMgr::GetI()->Update();
	Rectangle(mMemDC, -1, -1, mPtResolution.x + 1, mPtResolution.y + 1);
	CSceneMgr::GetI()->Render(mMemDC);
	BitBlt(mhDC, 0, 0, mPtResolution.x, mPtResolution.y, mMemDC, 0, 0, SRCCOPY);

	CTimeMgr::GetI()->Render();

}


