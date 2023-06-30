#pragma once
#include "CObject.h"



enum class MONSTER_STATE
{
	None,
	Create,
	Death,
	Attack,
};


class CMonster :
	public CObject
{
private:
	Vec2        m_vCenterPos;
	float       m_fSpeed;
	float       m_fMaxDistance;
	int			m_iDir;	//1,-1

	int			mHp;

	CObject*	mpTarget;

	MONSTER_STATE mState;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _fspeed) { m_fSpeed = _fspeed; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetTarget(CObject* _object) { mpTarget = _object; }


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(CMonster);


private:
	void death();
	void attack();

public:
	CMonster();
	~CMonster();

	// Inherited via CObject
};

