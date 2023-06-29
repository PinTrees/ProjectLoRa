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

	// ���� ����ϴ� GDI Object
	HBRUSH mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN mArrPen[(UINT)PEN_TYPE::END];

public:

	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Run();

private:
	// ���� ����� �귯�� �� �� ����
	void CreateBrushPen();

public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	POINT	GetResolution() { return mPtResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }
};

