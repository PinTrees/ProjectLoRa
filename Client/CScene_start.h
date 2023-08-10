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

	float		mCurBossDelay;
	float		mBossDelay;

	bool		mbBossRespone;
	int			mMonsterWave;

	float		mTimer;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


private:
	void CreateMonster();
	void createBoss();
	void createEnvi();
	void createPlayer();


public:
	Scene_Start();
	virtual ~Scene_Start() override;
};

