#pragma once
#include "SkillObj.h"




class Boomerang_Obj :
    public SkillObj
{
private:
    Vect2       mvDir;

    float       mCurTime;
    float       mSpeed;             // �ӵ� ����
    float       mAccel;             // ���ӵ� ����
    float       mObjAngle;

    bool        mCollision;         // �浹 �ߴ��� ���ߴ��� �Ǵ��ϴ� ����

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

