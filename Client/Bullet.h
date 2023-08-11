#pragma once
#include "CObject.h"

struct tEffectLv
{
	// 레벨 비율
	int BounceLv;		// 팅김 레벨
	int PenetrationLv;	// 관통 레벨
	int AttakDamageLv;	// 공격력 레벨
};


struct tBullet
{
	float	damage;
	float	penetrationCount;
	float	splitCount;
	float	bounceCount;
};


class Bullet :
	public CObject
{
private:
	Vect2		m_vDir;
	wstring		mUID;

	float		mDelay;
	float		mCurDelay;

	tBullet		mInfo;


public:
	void SetInfo(const tBullet& info) { mInfo = info; }
	tBullet& GetInfo() { return mInfo; }

	void SetDir(Vect2	_vDir)
	{
		m_vDir = _vDir.Normalize();
		SetAngle(m_vDir.ToAngle());
	}
	void SetType(const wstring& _str) { mUID = _str; }


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Bullet);


public:
	virtual void OnCollisionEnter(CCollider* _pOther);


public:
	Bullet(const wstring& _type);
	virtual ~Bullet() override;
};

