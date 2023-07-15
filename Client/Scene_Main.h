#pragma once
#include "CScene.h"




class Scene_Main :
    public CScene
{
private:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

public:
    Scene_Main();
    ~Scene_Main();
};

