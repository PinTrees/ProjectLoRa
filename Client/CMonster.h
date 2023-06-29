#pragma once
#include "CObject.h"
class CMonster :
	public CObject
{
private:
	Vec2        m_vCenterPos;
	float       m_fSpeed;
	float       m_fMaxDistance;
	int			m_iDir;	//1,-1
public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _fspeed) { m_fSpeed = _fspeed; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
public:
	virtual void Update() override;

public:
	CMonster();
	~CMonster();
};

