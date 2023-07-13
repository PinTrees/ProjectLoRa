#pragma once
#include "CState.h"


class IdleState :
<<<<<<< Updated upstream
    public CState
=======
    public CState<MONSTER_STATE>
>>>>>>> Stashed changes
{



<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    IdleState();
    ~IdleState();
};

