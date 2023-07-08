#pragma once
#include "CState.h"




class AtkState :
    public CState
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    AtkState();
    ~AtkState();
};

