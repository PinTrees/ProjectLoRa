#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
	public CObject
{

private:
	CTexture* mPTex;

public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

private:
	void createMissile();

public:
	CPlayer();
	~CPlayer();
};

