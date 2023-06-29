#pragma once

class CCore
{
	SINGLE(CCore)
private:
	HWND	mhWnd; // 메인 윈도우핸들 가져오기
	POINT	mPtResolution;// 메인 윈도우 해상도 가져오기
	HDC		mhDC;		// 메인윈도우에 그릴 dc가져오기

	HBITMAP mhBit;
	HDC		mMemDC;

	// 자주 사용하는 GDI Object
	HBRUSH mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN mArrPen[(UINT)PEN_TYPE::END];

public:

	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Run();

private:
	// 자주 사용할 브러쉬 밑 펜 설정
	void CreateBrushPen();

public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	POINT	GetResolution() { return mPtResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }
};

