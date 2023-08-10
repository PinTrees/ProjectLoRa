#pragma once
#include "SkillObj.h"


class CCollider;


class Thunder_Obj :
    public SkillObj
{
private:
    float       mCurDelay;
    bool        mbEffect;

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther) override;

public:
    Thunder_Obj();
    virtual ~Thunder_Obj();
};

