#pragma once
#include "SkillObj.h"


class IceBolt_Effect :
    public SkillObj
{
private:
    CObject*    mvecIcedMon;

    float       mCurTime;
    float       mFreezeTime;
    float       mDeFrostTime;

    bool        mFreeze;


public:
    void SetTargetMonster(CObject* _obj) { mvecIcedMon = _obj; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);


public:
    IceBolt_Effect();
    virtual ~IceBolt_Effect();
};

