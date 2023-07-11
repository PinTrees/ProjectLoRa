#pragma once
#include "CState.h"




class DeadState :
    public CState
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    DeadState();
    ~DeadState();
};