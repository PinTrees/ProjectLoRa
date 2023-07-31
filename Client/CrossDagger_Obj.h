#pragma once
#include "SkillObj.h"
class CrossDagger_Obj :
    public SkillObj
{
private:
    float       mCurTime;
    float       mTheta;
    float       mObjAngle;

public:
    void SetTheta(float _theta) { mTheta = _theta; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther) {}; // �浹 ���� ��� ȣ��Ǵ� �Լ�

public:
    CrossDagger_Obj();
    ~CrossDagger_Obj();
};

