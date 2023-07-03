#pragma once

#include "CObject.h"

class CTexture;
class CTile :
	public CObject
{
private:
	CTexture*	mpTileTex;
	int			miImgIdx;

public:
	void SetTexture(CTexture* _pTex) { mpTileTex = _pTex; }

	void AddImgIdx()
	{
		++miImgIdx;
	}

private:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(CTile);
public:

	CTile();
	~CTile();
};

