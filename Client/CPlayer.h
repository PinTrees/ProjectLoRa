#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
	public CObject
{

private:

public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

private:
	void createMissile();

	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};

