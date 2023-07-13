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

public:
	vector<uint8_t> Save();
	void Load(FILE* file);

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Tile);

public:
	Tile();
<<<<<<< Updated upstream
	~Tile();
=======
	virtual ~Tile();
>>>>>>> Stashed changes
};

