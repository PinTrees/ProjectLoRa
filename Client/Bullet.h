#pragma once
#include "CObject.h"

struct tEffectLv
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
	Vect2		m_vDir;
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
	void SetDir(Vect2	_vDir)
	{
		m_vDir = _vDir.Normalize();
		SetAngle(m_vDir.ToAngle());
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

