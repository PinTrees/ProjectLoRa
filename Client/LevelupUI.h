#pragma once
#include "CUI.h"
#include "CPanelUI.h"
#include "LevelUpUIMgr.h"


class Player;
class TextUI;
class CBtnUI;


class LevelupUI :
    public CPanelUI
{
private:
    tLeveUpEvent    mInfo;

    TextUI*         mTitleText;
    TextUI*         mInfoText;
    CBtnUI*         mSelectBtn;


public:
    void SetEffect(tLeveUpEvent event);


private:
    void statusUp(STATEUP_TYPE state);
    void skillUp(SKILL_TYPE state);


public:
    void ApplyLevelUp();

    CLONE(LevelupUI);


public:
    LevelupUI();
    virtual ~LevelupUI();
};