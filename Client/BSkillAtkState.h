#pragma once

#include "CState.h"

class BSkillAtkState :
    public CState<MONSTER_STATE>
{
private:
    float mAtkDelay;
    float mCurDelay;


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    BSkillAtkState();
    ~BSkillAtkState();
};