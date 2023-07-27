#pragma once
#include "CScene.h"
class Scene_Astar :
    public CScene
{
private:


public:
	virtual void Update();		// Object Game Logic
	virtual void Render(HDC _dc);	// Scene Rendering


public:
	Scene_Astar();
	virtual ~Scene_Astar();
};

