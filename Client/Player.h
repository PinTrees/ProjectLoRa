#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	mFullHP = 100.f;			// �ִ�ü��
	float	mRegenerationHP = 0.f;		// ü�����
	float	mMoveSpeed = 300.f;			// �̵� �ӵ�
	float	mAtkDamage = 10.f;			// ���ݷ�
	float	mAtkSpeed = 10.f;			// ���ݽ��ǵ�
	float	mAtkRange = 500.f;			// ��Ÿ�
	float	mShotSpeed = 100.f;			// �Ѿ� �ӵ�
	float	mReloadSpeed = 50.f;		// �����ӵ�
	float	mShotAngle = 0.f;			// �߻� ����(���߷�)
	float	mShotCount = 1.f;			// �߻� �Ѿ� ����
	UINT	mPenetration = 0;			// ���� ��
	UINT	mSplitCount = 0;			// �п� ��
	UINT	mBounceCount = 0;			// ƨ�� ��
};


class CTexture;
class Gun;
class BarUI;
class LevelupUI;




class Player :
	public CObject
{
	friend class LevelupUI;
private:
	float			mfDelay;
	float			mfCurDelay;

	Vect2			mvDashDir;

	Gun*			mCurGun;

	PLAYER_STATE	mState;
	tPlayerInfo		mtPlayerInfo;

	int				mLevel;

	float			mExp;
	BarUI*			mExpBar;

	AI<PLAYER_STATE>* mAI;


public:

public:
	tPlayerInfo GetInfo() { return mtPlayerInfo; }
	void SetInfo(tPlayerInfo _info) { mtPlayerInfo = _info; }

	float GetMaxExp() { return 10.f * mLevel + 10.f; };
	float GetExp() { return mExp; };
	void  AddExp(float exp) { mExp += exp; }

	void SetAI(AI<PLAYER_STATE>* pAI) { mAI = pAI; mAI->SetOwner(this); }


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;


private:
	void createMissile();
	void calExp();

	CLONE(Player);


public:
	Player();
	~Player();
};

