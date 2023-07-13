#pragma once
#include "CUI.h"
#include "CPanelUI.h"

class Player;
class TextUI;
class CBtnUI;


class LevelupUI :
    public CPanelUI
{
private:
    LEVELUP_EFFECT  mEffect;
    TextUI*         mTitleText;
    CBtnUI*         mSelectBtn;


public:
    void SetEffect(LEVELUP_EFFECT _effect) { mEffect = _effect; }
    void SetTitle(const wstring& _str);


public:
    void ApplyLevelUp();

    CLONE(LevelupUI);


public:
    LevelupUI();
    virtual ~LevelupUI();
};