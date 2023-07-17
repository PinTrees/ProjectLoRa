#pragma once
#include "CScene.h"


class CUI;


class Scene_Main :
    public CScene
{
private:
    CUI*    mItemUI;


private:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    
private:
    void OpenItemDataUI();
    void CloseItemDataUI();

public:
    Scene_Main();
    ~Scene_Main();
};

