#pragma once
#include "CScene.h"

class CPlayer;

class CScene_start :
	public CScene
{

private:
	float		mfMstrDelay;
	float		mfCurDelay;

	CPlayer*	mPlayer;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


private:
	void CreateMonster();
	void createEnvi();

public:
	CScene_start();
	~CScene_start();
};

