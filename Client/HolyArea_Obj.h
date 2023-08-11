#pragma once
#include "SkillObj.h"




class HolyArea_Obj :
    public SkillObj
{
private:
    float       mTheta;             // 각도
    float       mAlpha;             // 명암
    float       mPlusAlpha;         // 명암에 추가하는 값
    int         mPrevLv;

public:
    void SetPrevLv(int _lv) { mPrevLv = _lv; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    HolyArea_Obj();
    virtual ~HolyArea_Obj();
};

