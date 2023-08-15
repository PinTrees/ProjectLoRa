#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND	mhWnd;			// ���� �������ڵ� ��������
	POINT	mPtResolution;	// ���� ������ �ػ� ��������
	HDC		mhDC;			// ���������쿡 �׸� dc��������

	CTexture* mpMemTex;

	// GDI Object [ HBRUSH, HPEN ]
	HBRUSH	mArrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	mArrPen[(UINT)PEN_TYPE::END];

	map<COLORREF, HBRUSH>	mMapBrush;
	map<COLORREF, HPEN>		mMapPen;

	// Title Menu Object
	HMENU	mhMenu;


public:
	int  Initialize(HWND _hWnd, POINT _ptResolution);
	void RUN();
	void Clear();
	void Delete();


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
		 auto iter = mMapBrush.find(color);

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

	HPEN GetPen(COLORREF color) 
	{
		auto iter = mMapPen.find(color);

		if (iter != mMapPen.end())
		{
			return iter->second;
		}
		else
		{
			HPEN pen = (HPEN)CreatePen(PS_SOLID, 1, color);
			mMapPen[color] = pen; // mMapPen.insert(std::make_pair(color, pen));
			return pen;
		}
	}


	HBRUSH GetBrush(BRUSH_TYPE _eType) {return mArrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return mArrPen[(UINT)_eType]; }
};

