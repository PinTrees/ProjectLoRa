#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	fullHP = 100.f;				// 최대체력
	float	curHp = 0.f;				// 체력
	float	regenerationHP = 0.f;		// 체력재생
	float	moveSpeed = 300.f;			// 이동 속도
	float	atkDamage = 10.f;			// 공격력
	float	atkSpeed = 10.f;			// 공격스피드
	float	atkRange = 500.f;			// 사거리
	float	shotSpeed = 100.f;			// 총알 속도
	float	reloadSpeed = 50.f;			// 장전속도
	float	shotAngle = 0.f;			// 발사 각도(명중률)
	float	shotCount = 1.f;			// 발사 총알 개수

	UINT	penetration = 0;			// 관통 수
	UINT	splitCount = 0;				// 분열 수
	UINT	bounceCount = 0;			// 튕김 수
};


class CTexture;
class Gun;
class Skill;
class BarUI;
class CImageUI;
class LevelupUI;




class Player :
	public CObject
{

private:
	float	mfDelay;
	float	mfCurDelay;
	Vect2	mvDir;

	int			mLevel;
	float		mExp;
	BarUI*		mExpBar;
	CImageUI*	mHpBar;

	tPlayerInfo			mtInfo;
	vector<Skill*>		mVecSkill;
	Gun*				mCurGun;

	AI<PLAYER_STATE>*	mAI;


public:
	tPlayerInfo GetInfo() { return mtInfo; }
	void SetInfo(tPlayerInfo _info) { mtInfo = _info; }

	float GetMaxExp() { return 10.f * mLevel + 10.f; };
	float GetExp() { return mExp; };
	void  AddExp(float exp) { mExp += exp; }

	Vect2 GetRunDir() { return mvDir; }
	Gun* GetCurGun() { return mCurGun; }

	void SetAI(AI<PLAYER_STATE>* pAI) { mAI = pAI; mAI->SetOwner(this); }
	AI<PLAYER_STATE>* GetAI() { return mAI; }


public:
	Skill* FindSkill(SKILL_TYPE type);


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;


private:
	void calExp();

	CLONE(Player);


public:
	Player();
	~Player();

	friend class LevelupUI;
};

