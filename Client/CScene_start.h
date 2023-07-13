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
	virtual void Render(HDC _dc);
	virtual void Exit();


private:
	void CreateMonster();
	void createEnvi();
	void createPlayer();

public:
	Scene_Start();
	~Scene_Start();
};

