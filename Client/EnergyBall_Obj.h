#pragma once
#include "SkillObj.h"
class EnergyBall_Obj :
    public SkillObj
{
private:
    Vect2       mvDir;      // ¹æÇâ °ª
    float       mCurDelay;

public:
    void SetDir(Vect2 _dir) { mvDir = _dir; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    EnergyBall_Obj();
    ~EnergyBall_Obj();

};

