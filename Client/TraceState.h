#pragma once
#include "CState.h"


class TraceState :
    public CState<MONSTER_STATE>
{
private:
    float mAstarDelay;
    float mCurDelay;

    Vect2 mTargetPath;
    int idx;

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;


public:
    TraceState();
    ~TraceState();
};

