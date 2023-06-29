#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenTYPE)
	: mhDC(_dc)
	, mhDefaultBrush(nullptr)
	, mhDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetI()->GetPen(_ePenTYPE);
	mhDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushTYPE)
	: mhDC(_dc)
	, mhDefaultBrush(nullptr)
	, mhDefaultPen(nullptr)
{
	HBRUSH	hBrush = CCore::GetI()->GetBrush(_eBrushTYPE);
	mhDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(mhDC, mhDefaultBrush);
	SelectObject(mhDC, mhDefaultPen);
}
