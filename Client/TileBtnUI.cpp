#include "pch.h"	
#include "TileBtnUI.h"

#include "CTexture.h"
#include "ToolMgr.h"

TileBtnUI::TileBtnUI()
	: mIdx(0)
{

}

TileBtnUI::~TileBtnUI()
{

}

void TileBtnUI::Render(HDC dc)
{
	if (nullptr == GetTexture())
		return;

	UINT width = GetTexture()->Width();
	UINT height = GetTexture()->Heigth();

	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;

	UINT curRow = (UINT)mIdx / maxCol;
	UINT curCol = (UINT)mIdx % maxCol;

	if (maxRow <= curRow)
		return;

	Vect2 vPos = IsCameraAffected() ? CCamera::GetI()->GetRenderPos(GetFinalPos()) : GetFinalPos();
	Vect2 vScale = GetScale();

	//툴씬일경우와 스타트씬일경우 랜더 다르게 구현
	TransparentBlt(dc
		, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, GetTexture()->GetDC()
		, (int)(curCol * TILE_SIZE)
		, (int)(curRow * TILE_SIZE)
		, TILE_SIZE
		, TILE_SIZE
		, RGB(255, 0, 255));

	CUI::Render(dc);		
	CUI::RenderChild(dc);

	if (IsLbtnDown())
	{
		RenderHover(dc, 128.f);
	}
	else if (IsMouseOnUI())
	{
		RenderHover(dc, 32.f);
	}
}

void TileBtnUI::MouseOn()
{
	CBtnUI::MouseOn();
}

void TileBtnUI::MouseLbtnClick()
{
	ToolMgr::GetI()->SetTileIdx(mIdx);
}
