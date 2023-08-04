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
	virtual void Enter();
	virtual void Update();
	virtual void Exit();


private:
	void CreateBoss();
	void CreateMonster();
	void createEnvi();
	void createPlayer();


public:
	Scene_Start();
	~Scene_Start();
};

