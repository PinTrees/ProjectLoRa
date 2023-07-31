#pragma once
#include "SkillObj.h"
class CombatBall_Bullet :
    public SkillObj
{
private:
    Vect2           mvStartPoint;
    Vect2           mvCurvePoint;         // �Ѿ��� �ֱ� �����ϴ� ����
    Vect2           mvTarget;

    float           mCurTime;
    float           mRemainTime;          // 1 - mCurTime
    float           mArrivalTime;         // ��ǥ���� �����Ҷ� ������ �ð�

public:
    void SetStartPoint(Vect2 _start) { mvStartPoint = _start; }
    void SetCurvePoint(Vect2 _curvPoint) { mvCurvePoint = _curvPoint; }
    void SetTarget(Vect2 _target) { mvTarget = _target; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�

public:
    CombatBall_Bullet();
    ~CombatBall_Bullet();
};

