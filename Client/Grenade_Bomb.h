#pragma once
#include "SkillObj.h"




class Grenade_Bomb :
    public SkillObj
{
private:
    float       mCurDelay;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    Grenade_Bomb();
    ~Grenade_Bomb();
};

