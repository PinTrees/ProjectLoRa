#pragma once
#include "CObject.h"

struct Effect
{
	// ���� ����
	int BounceLv;		// �ñ� ����
	int PenetrationLv;	// ���� ����
	int AttakDamageLv;	// ���ݷ� ����
};

class Bullet :
	public CObject
{
private:
	float		m_tTheta; // �̵� ����
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

