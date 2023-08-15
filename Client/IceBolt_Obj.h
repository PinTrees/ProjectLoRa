#pragma once
#include "SkillObj.h"


class IceBolt_Obj :
    public SkillObj
{
private:
    Vect2       mvDir;
    float       mCurDelay;
    float       mRange;


public:
    void SetDir(Vect2 _dir) { mvDir = _dir; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther) {};


public:
    IceBolt_Obj();
    virtual ~IceBolt_Obj();
};

