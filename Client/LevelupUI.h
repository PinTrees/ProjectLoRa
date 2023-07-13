#pragma once
#include "CUI.h"

class Player;

class LevelupUI :
    public CUI
{
private:
    LEVELUP_EFFECT  mEffect;
    wstring         mStrEffect;
    CUI*            mpLeader;
    Player*         mpPlayer;

public:
    void SetEffect(LEVELUP_EFFECT _effect) { mEffect = _effect; }
    void SetString(const wstring& _str) { mStrEffect = _str; }

    CUI* GetLeaderUI() { return mpLeader; }
public:
    void CreateLevelupUI(Player* _player, Vect2 _pos);
    void ApplyLevelUp();

    CLONE(LevelupUI);
public:
    LevelupUI();
    virtual ~LevelupUI();
};

