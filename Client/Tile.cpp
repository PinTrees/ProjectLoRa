#include "pch.h"
#include "Tile.h"

#include "CCamera.h"
#include "CTexture.h"

Tile::Tile()
	: mpTileTex(nullptr)
	, mIdx(0)
{
<<<<<<< Updated upstream
	SetScale(Vec2(TILE_SIZE * 2, TILE_SIZE * 2));
=======
	SetScale(Vect2(TILE_SIZE * 2, TILE_SIZE * 2));
>>>>>>> Stashed changes
}


Tile::~Tile()
{

}




void Tile::Update()
{
}


void Tile::Render(HDC _dc)
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

<<<<<<< Updated upstream
	Vec2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());
	Vec2 vLocalPos = GetLocalPos();

	Vec2 vScale = GetScale();
=======
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());
	Vect2 vLocalPos = GetLocalPos();

	Vect2 vScale = GetScale();
>>>>>>> Stashed changes

	TransparentBlt(_dc
		, (int)vLocalPos.x
		, (int)vLocalPos.y
		, (int)(vScale.x)
		, (int)(vScale.y)
		, mpTileTex->GetDC()
		, (int)(curCol * TILE_SIZE)
		, (int)(curRow * TILE_SIZE)
		, TILE_SIZE
		, TILE_SIZE
		, RGB(255, 0, 255));
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
