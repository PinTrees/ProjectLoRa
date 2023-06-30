#pragma once

#include "CObject.h"

class CTexture;
class CTile :
	public CObject
{
private:
	CTexture*	mpTileTex;
	int			miIdx;

public:
	void SetTexture(CTexture* _pTex) { mpTileTex = _pTex; }


private:
	virtual void Update();
	virtual void Render(HDC _dc);
	CLONE(CTile);
public:

	CTile();
	~CTile();
};

