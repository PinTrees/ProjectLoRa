#pragma once
#include "CObject.h"


class Skill;



class SkillObj :
    public CObject
{
private:
    Skill* mpOwner;

    float       mCurDamageDelay;    // 데미지를 입히는 시간을 재는 용도
    float       mMaxDelay;			// 지속 시간

    float       mDamageDelay;       // 데미지 사이의 시간 차

    int         mCurDamageCount;    // 몬스터를 때린 횟수
    int         mDamageCount;       // 몬스터를 때릴 최대 횟수


public:
    void SetOwner(Skill* _owner) { mpOwner = _owner; }
    Skill* GetOwner() { return mpOwner; }

    void SetDamageDelay(float _ddelay) { mDamageDelay = _ddelay; mCurDamageDelay = _ddelay; } // 첫 스킬 데미지가 바로 들어가도록 초기화

    void SetDamageCount(int _ddcount) { mDamageCount = _ddcount; }

    void SetMaxDelay(float _max) { mMaxDelay = _max; }
    float GetMaxDelay() { return mMaxDelay; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionStay(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수

    CLONE(SkillObj);


public:
    SkillObj();
    virtual ~SkillObj();
};

