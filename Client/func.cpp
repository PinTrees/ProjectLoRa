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





void FlipImage(HDC hdc, int x, int y, int width, int height, HDC srcDC, int srcX, int srcY, int srcWidth, int srcHeight)
{
    // 플립된 이미지를 그릴 메모리 DC 생성
    HDC flipDC = CreateCompatibleDC(hdc);
    HBITMAP flipBitmap = CreateCompatibleBitmap(hdc, width, height);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(flipDC, flipBitmap);

    // 이미지를 수평으로 뒤집기 위한 변환 행렬 생성
    XFORM transform;
    transform.eM11 = -1.0f;
    transform.eM12 = 0.0f;
    transform.eM21 = 0.0f;
    transform.eM22 = 1.0f;
    transform.eDx = srcWidth;
    transform.eDy = 0.0f;

    // 변환 행렬 설정
    SetGraphicsMode(flipDC, GM_ADVANCED);
    SetWorldTransform(flipDC, &transform);

    // 원본 이미지를 플립된 메모리 DC에 그리기
    BitBlt(flipDC, 0, 0, width, height, srcDC, srcX, srcY, SRCCOPY);

    // 변환 행렬 초기화
    ModifyWorldTransform(flipDC, nullptr, MWT_IDENTITY);
    SetWorldTransform(flipDC, nullptr);

    // 플립된 이미지를 출력
    TransparentBlt(hdc, x, y, width, height, flipDC, 0, 0, srcWidth, srcHeight, RGB(255, 0, 255));

    // 메모리 해제
    SelectObject(flipDC, oldBitmap);
    DeleteObject(flipBitmap);
    DeleteDC(flipDC);
}
