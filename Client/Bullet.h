#pragma once
#include "CObject.h"

class Bullet :
	public CObject
{
private:
	float     m_tTheta; // 이동 방향
	Vec2		m_vDir;
	wstring		mType;

	float		mDelay;
	float		mCurDelay;

public:
	void SetDir(float _tTheta) { m_tTheta = _tTheta; }
	void SetDir(Vec2	_vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();

		float angle = atan2f(_vDir.y, _vDir.x) * 180.0f / PI;
		if (angle < 0.0f)
			angle += 360.0f;

		SetAngle(angle);
		SetAngleOffset(180);
	}
	void SetType(const wstring& _str) { mType = _str; }

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Bullet);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
public:
	Bullet(const wstring& _type);
	~Bullet();
};

