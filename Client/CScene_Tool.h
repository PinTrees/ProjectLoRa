#pragma once
#include "CScene.h"

class CUI;

class CScene_Tool :
	public CScene
{
private:
	CUI* mpUI;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();


	void SaveTileData();
	void SaveTile(const wstring& _strRelativePath);

public:
	CScene_Tool();
	~CScene_Tool();
};

