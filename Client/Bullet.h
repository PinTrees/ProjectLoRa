#pragma once
#include "CObject.h"

struct Effect
{
	// 레벨 비율
	int BounceLv;		// 팅김 레벨
	int PenetrationLv;	// 관통 레벨
	int AttakDamageLv;	// 공격력 레벨
};

class Bullet :
	public CObject
{
private:
	float		m_tTheta; // 이동 방향
	Vec2		m_vDir;
	wstring		mType;

	float		mDelay;
	float		mCurDelay;

	int			mPenetrationCount;
	int			mDivideCount;
	int			mBounceCount;

public:
	void SetDivideCount(int _count) { mDivideCount = _count; }
	void SetPenetrationCount(int _count) { mPenetrationCount = _count; }
	void SetBounceCount(int _count) { mBounceCount = _count; }

	void SetDir(float _tTheta) { m_tTheta = _tTheta; }
	void SetDir(Vec2	_vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();

		float angle = atan2f(_vDir.y, _vDir.x) * 180.0f / PI;
		if (angle < 0.0f)
			angle += 360.0f;

		SetAngle(angle);
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
	//Bullet(const Bullet& _clone);
	~Bullet();
};

