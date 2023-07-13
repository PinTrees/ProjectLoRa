#pragma once

#include "CObject.h"


struct tGunInfo
{
	float	mAtkDamage;		// ���ݷ�
	float	mAtkSpeed;		// ���ݽ��ǵ�
	float	mAtkRange;		// ��Ÿ�
	float	mShotSpeed;		// �Ѿ� �ӵ�
	float	mReloadSpeed;	// �����ӵ�
	float	mShotAngle;		// �߻� ����(���߷�)
	float	mShotCount;		// �߻� �Ѿ� ����
	float	mBulletCount;	// �Ѿ� ����
	UINT	mPenetration;	// ���� ��
};


class Player;




class Gun :
	public CObject
{
private:
	float     m_tTheta; // �̵� ����
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

