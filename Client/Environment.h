#pragma once

#include "CObject.h"


class Environment
	: public CObject
{
private:
	wstring mType;
	int xIdx;
	int yIdx;

public:
	void DistoryEnvi();
	void SetIdx(int _x, int _y) { xIdx = _x; yIdx = _y; }


public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

	CLONE(Environment);


public:
	Environment(const wstring& _type);
	~Environment();
};

