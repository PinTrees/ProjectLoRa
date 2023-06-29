#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float     m_tTheta; // 이동 방향


	Vec2		m_vDir;
public:
	void SetDir(float _tTheta) { m_tTheta = _tTheta; }
	void SetDir(Vec2	_vDir) 
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

