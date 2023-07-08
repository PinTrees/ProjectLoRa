#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore)
private:
	HWND	mhWnd; // 메인 윈도우핸들 가져오기
	POINT	mPtResolution;// 메인 윈도우 해상도 가져오기
	HDC		mhDC;		// 메인윈도우에 그릴 dc가져오기
	
	CTexture* mpMemTex;		// 백버퍼 텍스쳐

	// 자주 사용하는 GDI Object
	HBRUSH mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN mArrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU	mhMenu; // Tool Scene에만 사용

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

