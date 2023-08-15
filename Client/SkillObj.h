#pragma once
#include "CObject.h"


class Skill;



class SkillObj :
    public CObject
{
private:
    Skill*      mpOwner;

    float       mDamage;

    float       mCurDamageDelay;    // �������� ������ �ð��� ��� �뵵
    float       mMaxDelay;			// ���� �ð�

    float       mDamageDelay;       // ������ ������ �ð� ��

    int         mCurDamageCount;    // ���͸� ���� Ƚ��
    int         mDamageCount;       // ���͸� ���� �ִ� Ƚ��


public:
    void SetOwner(Skill* _owner) { mpOwner = _owner; }
    Skill* GetOwner() { return mpOwner; }

    void SetDamage(float _damage) { mDamage = _damage; }
    float GetDamage() { return mDamage; }

    void SetDamageDelay(float _ddelay) { mDamageDelay = _ddelay; mCurDamageDelay = _ddelay; } // ù ��ų �������� �ٷ� ������ �ʱ�ȭ

    void SetDamageCount(int _ddcount) { mDamageCount = _ddcount; }

    void SetMaxDelay(float _max) { mMaxDelay = _max; }
    float GetMaxDelay() { return mMaxDelay; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�

    CLONE(SkillObj);


public:
    SkillObj();
    virtual ~SkillObj();
};

