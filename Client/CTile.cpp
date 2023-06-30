#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	:mpTileTex(nullptr)
	, miIdx(33)  
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{
	if (nullptr == mpTileTex || -1 == miIdx) //텍스쳐가 없으면 안그림
		return;

	UINT iWidth =  mpTileTex->Width();
	UINT iHeight = mpTileTex->Heigth();

	UINT iMaxCol = (UINT)iWidth / TILE_SIZE;
	UINT iMaxRow = (UINT)iHeight / TILE_SIZE;

	UINT iCurRow = miIdx / iMaxCol;
	UINT iCurCol = miIdx % iMaxCol;

	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2	vRenderPos = CCamera::GetI()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(_dc
		, vRenderPos.x
		, vRenderPos.y
		, vScale.x
		, vScale.y
		, mpTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}