#pragma once
#include "CScene.h"


class CUI;
class CImageUI;


class Scene_Main :
    public CScene
{
private:
    CUI*    mItemUI;
    CImageUI* mPressBack;

    float   mFadeDelay;
    float   mCurDelay;
    int     mFadeDir;


private:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    
public:
    void OpenItemDataUI();
    void CloseItemDataUI();


public:
    Scene_Main();
    ~Scene_Main();
};

