#pragma once
#include "CState.h"


class AtkState :
    public CState<MONSTER_STATE>
{
private:
    bool        mAtkAvailable;

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    AtkState();
    ~AtkState();
};

