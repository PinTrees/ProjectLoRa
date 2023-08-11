#pragma once
#include "CObject.h"



class Monster_Arrow :
    public CObject
{
private:
    CObject*        mpOwner;

    Vect2           mvDir;
    float           mCurTime;
    bool            mbDestroy;


public:
    void SetDir(Vect2 _dir) { mvDir = _dir; }

    void SetOwner(CObject* _owner) { mpOwner = _owner; }
    CObject* GetOwner() { return mpOwner; }


public:
    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(Monster_Arrow);


public:
    Monster_Arrow();
    virtual ~Monster_Arrow() override;
};

