#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore)
private:
	HWND	mhWnd; // ���� �������ڵ� ��������
	POINT	mPtResolution;// ���� ������ �ػ� ��������
	HDC		mhDC;		// ���������쿡 �׸� dc��������
	
	CTexture* mpMemTex;		// ����� �ؽ���

	// ���� ����ϴ� GDI Object
	HBRUSH mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN mArrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU	mhMenu; // Tool Scene���� ���

public:

	int Initialize(HWND _hWnd, POINT _ptResolution);
	void Run();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);


public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	HMENU	GetMenu()	{return mhMenu;}


	POINT	GetResolution() { return mPtResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }

};

