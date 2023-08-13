#pragma once
#include "CState.h"




class PDashState :
    public CState<PLAYER_STATE>
{
private:
    Vect2 mvDashDir;
    float mDashTime;

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    PDashState();
    virtual ~PDashState();
};
