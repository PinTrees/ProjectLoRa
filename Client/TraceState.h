#pragma once
#include "CState.h"


class TraceState :
<<<<<<< Updated upstream
    public CState
=======
    public CState<MONSTER_STATE>
>>>>>>> Stashed changes
{
private:


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    TraceState();
    ~TraceState();
};

