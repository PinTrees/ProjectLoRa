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

	CUI*		mpSettingBtn;


public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


private:
	void CreateMonster();
	void createEnvi();
	void createPlayer();
	void createMainUI();


public:
	void OpenSettingPanel();


public:
	Scene_Start();
	~Scene_Start();
};

