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
	CLONE(CTile);
public:

	CTile();
	~CTile();
};

