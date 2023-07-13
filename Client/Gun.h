#pragma once

#include "CObject.h"

<<<<<<< Updated upstream
class Player;


=======

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




>>>>>>> Stashed changes
class Gun :
	public CObject
{
private:
	float     m_tTheta; // �̵� ����
	wstring		mType;

	Player*	mOwner;

	float		mDelay;
	float		mCurDelay;

<<<<<<< Updated upstream
	float	mAtkDamage;		// ���ݷ�
	float	mAtkSpeed;		// ���ݽ��ǵ�
	float	mAtkRange;		// ��Ÿ�
	float	mShotSpeed;		// �Ѿ� �ӵ�
	float	mReloadSpeed;	// �����ӵ�
	float	mShotAngle;		// �߻� ����(���߷�)
	UINT	mPenetration;	// ���� ��
=======
	tGunInfo	mInfo;
>>>>>>> Stashed changes


public:
	void SetType(const wstring& _str) { mType = _str; }
	void SetOwner(Player* _owner) { mOwner = _owner; }

<<<<<<< Updated upstream
=======
	const tGunInfo& GetInfo() { return mInfo; }

public:
	void Shot();

>>>>>>> Stashed changes

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
	Gun(const wstring& _type);
	~Gun();
};

