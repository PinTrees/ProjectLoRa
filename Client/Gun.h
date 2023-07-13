#pragma once

#include "CObject.h"


struct tGunInfo
{
	float	atkDamage;		// 공격력
	float	atkSpeed;		// 공격스피드
	float	atkRange;		// 사거리
	float	shotSpeed;		// 총알 속도
	float	shotAngle;		// 발사 각도(명중률)
	
	float	reloadSpeed;	// 장전속도
	float	shotDelay;		// 총알 발사 딜레이

	UINT	shotCount;		// 발사 총알 개수
	UINT	bulletCount;	// 장전 총알 개수
	UINT	curBulletCount = 0;

	UINT	penetration;	// 관통 수
	UINT	splitCount;		// 분열 수
	UINT    bouncCount;		// 튕김 수

	wstring texture;
	wstring bulletType;
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
	bool		mbReload;


public:
	void SetType(const wstring& _str) { mType = _str; }
	void SetOwner(Player* _owner) { mOwner = _owner; }

	const tGunInfo& GetInfo() { return mInfo; }

public:
	void Shot();
	void Reload();


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
	Gun(const wstring& _type);
	~Gun();
};

