#pragma once
#include "CScene.h"

class CScene_Tool :
	public CScene
{
private:

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Tool();
	~CScene_Tool();
};

