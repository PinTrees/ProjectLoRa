#pragma once
#include "CScene.h"

class CUI;

class Scene_Tool :
	public CScene
{
private:
	CUI* mpUI;

	UINT	mTileX;
	UINT	mTileY;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Render(HDC _dc);
	virtual void Exit();

public:
	void SetTileIdx();

	void SetTileX(UINT x) { mTileX = x; }
	void SetTileY(UINT y) { mTileY = y; }

	UINT GetTileX() { return mTileX; }
	UINT GetTileY() { return mTileY; }

	void SaveTileData();
	void LoadTIleData();

	void SaveTile(const wstring& _strRelativePath);
	void LoadTile(const wstring& _strRelativePath);


private:
	void render_tile(HDC _dc);


public:
	Scene_Tool();
	~Scene_Tool();
};

