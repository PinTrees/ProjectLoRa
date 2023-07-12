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

	map<COLORREF, HBRUSH> mMapBrush;
		 
	// Title Menu Object
	HMENU	mhMenu;

public:
	int  Initialize(HWND _hWnd, POINT _ptResolution);
	void RUN();
	void Clear();


private:
	// ���� ����� �귯�� �� �� ����
	void CreateBrushPen();


public:
	void SetActiveMenu(bool active);
	void ChangeWindowSize(Vect2 vResoulution, bool menuActive);


public:
	HWND	GetMainHwnd() { return mhWnd; }
	HDC		GetMainDC() { return mhDC; }
	POINT	GetResolution() { return mPtResolution; }
	HMENU   GetMenu() { return mhMenu; }

	HBRUSH GetBrush(COLORREF color) 
	{
		 map<COLORREF, HBRUSH>::iterator iter = mMapBrush.find(color);

		 if (iter != mMapBrush.end()) 
		 {
			 return iter->second;
		 }
		 else
		 {
			 HBRUSH brush = (HBRUSH)CreateSolidBrush(color);
			 mMapBrush.insert(make_pair(color, brush));
		 
			 return brush;
		 }
	}

	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }
};

