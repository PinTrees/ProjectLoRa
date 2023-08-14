#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND	mhWnd;			// 메인 윈도우핸들 가져오기
	POINT	mPtResolution;	// 메인 윈도우 해상도 가져오기
	HDC		mhDC;			// 메인윈도우에 그릴 dc가져오기

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
	// 자주 사용할 브러쉬 밑 펜 설정
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

