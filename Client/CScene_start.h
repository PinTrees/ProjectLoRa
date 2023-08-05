#pragma once
#include "CScene.h"

class Player;
class CUI;

class Scene_Start :
	public CScene
{

private:
	float		mfMstrDelay;
	float		mfCurDelay;

	int			mMonsterWave;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


private:
	void CreateMonster();
	void createEnvi();
	void createPlayer();


public:
	Scene_Start();
	~Scene_Start();
};

