#pragma once
#include "CScene.h"

class CScene_start :
	public CScene
{
private:
	Vec2	mvForcePos;
	float	mfForceRadius;
	float	mfCurRadius;
	float mfForce;
	bool	mbUseForce;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void Enter();
	virtual void Exit();


public:
	void CreateForce();

public:
	CScene_start();
	~CScene_start();
};

