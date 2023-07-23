#pragma once
#include "SkillObj.h"
class CirclingBall_Obj :
    public SkillObj
{
private:
    int         mPrevLv;        // ��ų�� ���� ����
    float       mTheta;         // ����

public:
    void SetTheta(float _theta) { mTheta = _theta; }

    void SetPrevLv(int _Lv) { mPrevLv = _Lv; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CirclingBall_Obj();
    ~CirclingBall_Obj();

};

