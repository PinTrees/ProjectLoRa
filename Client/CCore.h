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
public:

	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Run();

public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	POINT	GetResolution() { return mPtResolution; }
};

