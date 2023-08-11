#pragma once

#include "CObject.h"


class CTexture;


class Environment
	: public CObject
{
private:
	wstring mType;
	int xIdx;
	int yIdx;

	CTexture* mpTex;
	CTexture* mpShadowTex;

	Vect2 mvShadowOffset;
	Vect2 mvShadowScale;


public:
	void DistoryEnvi();
	void SetIdx(int _x, int _y) { xIdx = _x; yIdx = _y; }


public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

	CLONE(Environment);


public:
	Environment(const wstring& _type);
	virtual ~Environment() override;
};

