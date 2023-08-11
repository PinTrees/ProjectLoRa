#pragma once
#include "CObject.h"

class Stone :
    public CObject
{

private:
    Vect2       mvStartPoint;       // ������Ʈ�� �����
    Vect2       mvTargetPoint;      // ������Ʈ�� ��ǥ����
    Vect2       mvCurvePoint;       // ������Ʈ�� ��������� �ֵ����ϴ� ��ǥ

    float       mCurTime;
    float       mArrivalTime;       // ��ǥ������ ������ �� ������ �ð�
    float       mRemainTime;        // 1 - mCurTime

    //CSound* mpSound;

public:
    void SetStartPoint(Vect2 _vPos) { mvStartPoint = _vPos; }
    void SetCurvePoint(Vect2 _vPos) { mvCurvePoint = _vPos; }
    void SetTargetPoint(Vect2 _vPos) { mvTargetPoint = _vPos; }

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(Stone);
public:

	Stone();
	~Stone();
};

