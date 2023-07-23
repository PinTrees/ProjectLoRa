#pragma once
#include "SkillObj.h"
class Thunder_Obj :
    public SkillObj
{
private:
    float       mCurDelay;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    Thunder_Obj();
    ~Thunder_Obj();

};

