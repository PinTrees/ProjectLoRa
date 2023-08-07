#pragma once
#include "CState.h"




class PDieState :
    public CState<PLAYER_STATE>
{
private:

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    PDieState();
    ~PDieState();
};

