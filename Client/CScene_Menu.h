#pragma once
#include "CScene.h"

class CScene_Menu :
    public CScene
{
private:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Menu();
    ~CScene_Menu();
};

