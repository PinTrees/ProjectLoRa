#include "pch.h"
#include "Tile.h"

#include "CCamera.h"
#include "CTexture.h"

#include "SelectGDI.h"

Tile::Tile()
	: mpTileTex(nullptr)
	, mIdx(0)
{
	SetScale(Vect2(TILE_SIZE * 2, TILE_SIZE * 2));
}


Tile::~Tile()
{

}




void Tile::Update()
{
}


void Tile::Render(HDC _dc, bool editor)
{
	if (nullptr == mpTileTex || -1 == mIdx)
		return;
	
	UINT width = mpTileTex->Width();
 	UINT height = mpTileTex->Heigth();

	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;

	UINT curRow = (UINT)mIdx / maxCol;
	UINT curCol = (UINT)mIdx % maxCol;

	if (maxRow <= curRow)
		return;

	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());
	Vect2 vLocalPos = GetLocalPos();

	Vect2 vScale = GetScale();

	TransparentBlt(_dc
		, editor ? (int)vRenderPos.x : (int)vLocalPos.x
		, editor ? (int)vRenderPos.y : (int)vLocalPos.y
		, (int)(vScale.x)
		, (int)(vScale.y)
		, mpTileTex->GetDC()
		, (int)(curCol * TILE_SIZE)
		, (int)(curRow * TILE_SIZE)
		, TILE_SIZE
		, TILE_SIZE
		, RGB(255, 0, 255));

	if (DEBUG)
	{
		SelectGDI p = SelectGDI(_dc, RGB(0, 0, 0), NULL);
		SelectGDI b = SelectGDI(_dc, BRUSH_TYPE::HOLLOW);

		Rectangle(_dc
			, vLocalPos.x
			, vLocalPos.y
			, vLocalPos.x + vScale.x
			, vLocalPos.y + vScale.y);
	}
}


vector<uint8_t> Tile::Save()
{
	vector<uint8_t> data;

	data.insert(data.end(), reinterpret_cast<uint8_t*>(&mIdx), reinterpret_cast<uint8_t*>(&mIdx) + sizeof(UINT));

	return data;
}

void Tile::Load(FILE* file)
{
	fread(&mIdx, sizeof(int), 1, file);
}
