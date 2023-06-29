#pragma once

class CCore
{
	SINGLE(CCore)
private:
	HWND	mhWnd; // ���� �������ڵ� ��������
	POINT	mPtResolution;// ���� ������ �ػ� ��������
	HDC		mhDC;		// ���������쿡 �׸� dc��������

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

