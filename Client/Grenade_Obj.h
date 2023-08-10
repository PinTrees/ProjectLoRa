#pragma once
#include "SkillObj.h"


class CSound;


class Grenade_Obj :
    public SkillObj
{
private:
    Vect2       mvStartPoint;       // 오브젝트의 출발점
    Vect2       mvTargetPoint;      // 오브젝트의 목표지점
    Vect2       mvCurvePoint;       // 오브젝트의 진행방향이 휘도록하는 좌표

    float       mCurTime;
    float       mArrivalTime;       // 목표지점에 도착할 때 까지의 시간
    float       mRemainTime;        // 1 - mCurTime

    CSound*     mpSound;


public:
    void SetStartPoint(Vect2 _vPos) { mvStartPoint = _vPos; }
    void SetCurvePoint(Vect2 _vPos) { mvCurvePoint = _vPos; }
    void SetTargetPoint(Vect2 _vPos) { mvTargetPoint = _vPos; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);


public:
    Grenade_Obj();
    virtual ~Grenade_Obj();
};

