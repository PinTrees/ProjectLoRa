#pragma once
#include "SkillObj.h"
class CombatBall_Bullet :
    public SkillObj
{
private:
    Vect2           mvStartPoint;
    Vect2           mvCurvePoint;         // 총알이 휘기 시작하는 지점
    Vect2           mvTarget;

    float           mCurTime;
    float           mRemainTime;          // 1 - mCurTime
    float           mArrivalTime;         // 목표물에 도착할때 까지의 시간

public:
    void SetStartPoint(Vect2 _start) { mvStartPoint = _start; }
    void SetCurvePoint(Vect2 _curvPoint) { mvCurvePoint = _curvPoint; }
    void SetTarget(Vect2 _target) { mvTarget = _target; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수

public:
    CombatBall_Bullet();
    ~CombatBall_Bullet();
};

