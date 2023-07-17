#pragma once

#include "CObject.h"

class CTexture;

class Tile
	: public CObject
{
private:
	CTexture*	mpTileTex;
	int			mIdx;

public:
	void SetTexture(CTexture* _tex) { mpTileTex = _tex; }
	void AddImgIdx()	{ ++mIdx; }
	void SetImgIdx(int _TileIdx) { mIdx = _TileIdx; }
public:
	vector<uint8_t> Save();
	void Load(FILE* file);

public:
	virtual void Update() override;
	void Render(HDC _dc, bool editor);

	CLONE(Tile);

public:
	Tile();
	~Tile();
};

