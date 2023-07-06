#pragma once
#include "CScene.h"

class Player;

class Scene_Start :
	public CScene
{

private:
	float		mfMstrDelay;
	float		mfCurDelay;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


private:
	void CreateMonster();
	void createEnvi();

public:
	Scene_Start();
	~Scene_Start();
};

