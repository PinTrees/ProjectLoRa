#pragma once

#include "CObject.h"

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

	float	mAtkDamage;		// ���ݷ�
	float	mAtkSpeed;		// ���ݽ��ǵ�
	float	mAtkRange;		// ��Ÿ�
	float	mShotSpeed;		// �Ѿ� �ӵ�
	float	mReloadSpeed;	// �����ӵ�
	float	mShotAngle;		// �߻� ����(���߷�)
	UINT	mPenetration;	// ���� ��


public:
	void SetType(const wstring& _str) { mType = _str; }
	void SetOwner(Player* _owner) { mOwner = _owner; }


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
	Gun(const wstring& _type);
	~Gun();
};

