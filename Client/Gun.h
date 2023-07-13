#pragma once

#include "CObject.h"


struct tGunInfo
{
	float	mAtkDamage;		// 공격력
	float	mAtkSpeed;		// 공격스피드
	float	mAtkRange;		// 사거리
	float	mShotSpeed;		// 총알 속도
	float	mReloadSpeed;	// 장전속도
	float	mShotAngle;		// 발사 각도(명중률)
	float	mShotCount;		// 발사 총알 개수
	float	mBulletCount;	// 총알 개수
	UINT	mPenetration;	// 관통 수
};


class Player;




class Gun :
	public CObject
{
private:
	float     m_tTheta; // 이동 방향
	wstring		mType;

	Player*	mOwner;

	float		mDelay;
	float		mCurDelay;

	tGunInfo	mInfo;


public:
	void SetType(const wstring& _str) { mType = _str; }
	void SetOwner(Player* _owner) { mOwner = _owner; }

	const tGunInfo& GetInfo() { return mInfo; }

public:
	void Shot();


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
	Gun(const wstring& _type);
	~Gun();
};

