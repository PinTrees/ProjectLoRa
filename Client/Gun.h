#pragma once

#include "CObject.h"


struct tGunInfo
{
	float	atkDamage;		// ���ݷ�
	float	atkSpeed;		// ���ݽ��ǵ�
	float	atkRange;		// ��Ÿ�
	float	shotSpeed;		// �Ѿ� �ӵ�
	float	shotAngle;		// �߻� ����(���߷�)
	
	float	reloadSpeed;	// �����ӵ�
	float	shotDelay;		// �Ѿ� �߻� ������

	UINT	shotCount;		// �߻� �Ѿ� ����
	UINT	bulletCount;	// ���� �Ѿ� ����
	UINT	curBulletCount = 0;

	UINT	penetration;	// ���� ��
	UINT	splitCount;		// �п� ��
	UINT    bouncCount;		// ƨ�� ��

	wstring texture;
	wstring bulletType;
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

