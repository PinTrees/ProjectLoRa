#pragma once
#include "SkillObj.h"
class CirclingBall_Obj :
    public SkillObj
{
private:
    int         mPrevLv;        // 스킬의 이전 레벨
    float       mTheta;         // 각도

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

