#pragma once
#include "CState.h"

class BAtkState :
    public CState<MONSTER_STATE>
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    BAtkState();
    ~BAtkState();
};