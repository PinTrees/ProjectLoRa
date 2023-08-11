#pragma once
#include "CState.h"


class PAtkState :
    public CState<PLAYER_STATE>
{
private:
    Vect2 mvDir;

    float mAtkDelay;
    float mCurDelay;


public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    PAtkState();
    virtual ~PAtkState();
};
