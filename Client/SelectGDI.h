#pragma once


class SelectGDI
{

private:
	HDC		mhDC;
	HPEN	mhDefaultPen;
	HBRUSH	mhDefaultBrush;

public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenTYPE);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushTYPE);
	~SelectGDI();
};

