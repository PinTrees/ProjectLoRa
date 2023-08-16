#pragma once
#include "CScene.h"

class CSound;
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
	bool		mbBossDead;
	int			mMonsterWave;

	float		mTimer;

	CSound*		mpBGM;
	CSound*		mpBGM_BOSS;
	CSound*		mpBGM_CLEAR;

public:
	void SetClear(bool clear) { mbBossDead = clear; }

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

