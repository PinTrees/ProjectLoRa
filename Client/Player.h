#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	mFullHP = 100.f;			// 최대체력
	float	mRegenerationHP = 0.f;		// 체력재생
	float	mMoveSpeed = 300.f;			// 이동 속도
	float	mAtkDamage = 10.f;			// 공격력
	float	mAtkSpeed = 10.f;			// 공격스피드
	float	mAtkRange = 500.f;			// 사거리
	float	mShotSpeed = 100.f;			// 총알 속도
	float	mReloadSpeed = 50.f;		// 장전속도
	float	mShotAngle = 0.f;			// 발사 각도(명중률)
	float	mShotCount = 1.f;			// 발사 총알 개수
	UINT	mPenetration = 0;			// 관통 수
	UINT	mSplitCount = 0;			// 분열 수
	UINT	mBounceCount = 0;			// 튕김 수
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

