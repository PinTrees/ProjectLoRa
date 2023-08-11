#pragma once
#include "SkillObj.h"




class HolyArea_Obj :
    public SkillObj
{
private:
    float       mTheta;             // ����
    float       mAlpha;             // ���
    float       mPlusAlpha;         // ��Ͽ� �߰��ϴ� ��
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

