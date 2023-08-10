#pragma once
#include "CState.h"




class DeadState :
    public CState<MONSTER_STATE>
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    DeadState();
    virtual ~DeadState();
};