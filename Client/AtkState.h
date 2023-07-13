#pragma once
#include "CState.h"


<<<<<<< Updated upstream


class AtkState :
    public CState
=======
class AtkState :
    public CState<MONSTER_STATE>
>>>>>>> Stashed changes
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

