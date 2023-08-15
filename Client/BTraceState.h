#pragma once
#include "CState.h"


class BTraceState :
    public CState<MONSTER_STATE>
{

private:
    float fCurSkillCool;
    float fSkillCool;
    bool mAvailable;

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    BTraceState();
    ~BTraceState();
};
