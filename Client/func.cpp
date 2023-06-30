#include "pch.h"
#include "func.h"

#include "CEventMgr.h"


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


Vec2 curvesCircle(Vec2 c1, float _radius, float _amount)
{
	float angle = _amount * 2 * PI;

	float x = c1.x + _radius * cos(angle);
	float y = c1.y + _radius * sin(angle);

	return Vec2(x, y);
}





void FlipImage(HDC _dc, int _x, int _y, int _width, int _height)
{
	HDC hMemDC = CreateCompatibleDC(_dc);
	HBITMAP hBitmap = CreateCompatibleBitmap(_dc, _width, _height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	// 이미지를 플립하여 복사
	StretchBlt(hMemDC, 0, 0, _width, _height, _dc, _x + _width, _y, -_width, _height, SRCCOPY);

	// 플립된 이미지를 원래 위치로 복사
	BitBlt(_dc, _x, _y, _width, _height, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}