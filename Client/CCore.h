#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore)
private:
	HWND	mhWnd; // ���� �������ڵ� ��������
	POINT	mPtResolution;// ���� ������ �ػ� ��������
	HDC		mhDC;		// ���������쿡 �׸� dc��������

	CTexture* mpMemTex;

	// GDI Object [ HBRUSH, HPEN ]
	HBRUSH	mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	mArrPen[(UINT)PEN_TYPE::END];

	// Title Menu Object
	HMENU	mhMenu;

public:
	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Run();
	void Clear();


private:
	// ���� ����� �귯�� �� �� ����
	void CreateBrushPen();


public:
	void SetActiveMenu(bool active);
	void ChangeWindowSize(Vec2 vResoulution, bool menuActive);


public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	POINT	GetResolution() { return mPtResolution; }
	HMENU   GetMenu() { return mhMenu; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }
};

