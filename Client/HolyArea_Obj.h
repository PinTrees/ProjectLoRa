#pragma once
#include "SkillObj.h"




class HolyArea_Obj :
    public SkillObj
{
private:
    float       mTheta;             // °¢µµ
    int         mPrevLv;

    float       mFadeDelay;
    float       mCurDelay;
    float       mFadeDir;


public:
    void SetPrevLv(int _lv) { mPrevLv = _lv; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    HolyArea_Obj();
    virtual ~HolyArea_Obj();
};

