#pragma once
#include "CScene.h"


class CUI;
class CImageUI;
class HelpDialogUI;

class Scene_Main :
    public CScene
{
private:
    CUI*        mItemUI;
    CImageUI*   mPressBack;
    CImageUI*   mpPlayerThumb;

    HelpDialogUI* mDialogHelp;

    float       mFadeDelay;
    float       mCurDelay;
    int         mFadeDir;


private:
    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    
public:
    void OpenHelpDialog();
    void CloseItemDataUI();

    void OpenInfoDialog();
    void CloseInfoDialog();


public:
    Scene_Main();
    virtual ~Scene_Main() override;
};

