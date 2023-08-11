#pragma once
#include "SkillObj.h"




class CombatBall_Obj :
    public SkillObj
{
private:
    float       mSpeed;
    float       mCurTime;
    float       mTheta;
    int         mPrevLv;

    bool        mLeft;

public:
    void SetPrevLv(int _Lv) { mPrevLv = _Lv; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CombatBall_Obj();
    virtual ~CombatBall_Obj();
};

