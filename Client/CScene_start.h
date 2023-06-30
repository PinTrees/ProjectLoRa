#pragma once
#include "CScene.h"

class CScene_start :
	public CScene
{
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
public:
	CScene_start();
	~CScene_start();
};

