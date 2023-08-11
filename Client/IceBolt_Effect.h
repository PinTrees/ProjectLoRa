#pragma once
#include "SkillObj.h"
class IceBolt_Effect :
    public SkillObj
{
private:
    vector<CObject*> mvecIcedMon;

    float       mCurTime;
    float       mFreezeTime;
    float       mDeFrostTime;

    bool        mFreeze;

public:
    void AddIceMonster(CObject* _obj) { mvecIcedMon.push_back(_obj); }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    IceBolt_Effect();
    ~IceBolt_Effect();
};

