#pragma once
#include "SkillObj.h"




class Boomerang_Obj :
    public SkillObj
{
private:
    Vect2       mvDir;

    float       mCurTime;
    float       mSpeed;             // 속도 변수
    float       mAccel;             // 가속도 변수
    float       mObjAngle;

    bool        mCollision;         // 충돌 했는지 안했는지 판단하는 변수

public:
    void SetDir(Vect2 _dir) { mvDir = _dir; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    Boomerang_Obj();
    virtual ~Boomerang_Obj();
};

