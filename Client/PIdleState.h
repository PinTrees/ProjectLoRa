#pragma once
#include "CState.h"


class PIdleState :
    public CState<PLAYER_STATE>
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    PIdleState();
    virtual ~PIdleState();
};
