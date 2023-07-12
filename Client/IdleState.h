#pragma once
#include "CState.h"


class IdleState :
    public CState<MONSTER_STATE>
{



public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    IdleState();
    ~IdleState();
};

