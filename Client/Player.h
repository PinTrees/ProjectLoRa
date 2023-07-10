#pragma once
#include "CObject.h"

// 스테이트 패턴으로 변경 필요
enum class PLAYER_STATE
{
	NONE,
	Idle,
	ATTACK,
	Run,
	Die,
	Dash,
};


class CTexture;
class Gun;
class BarUI;




class Player :
	public CObject
{

private:
	float mfDelay;
	float mfCurDelay;

	Vect2 mvDashDir;

	Gun* mCurGun;

	PLAYER_STATE mState;

	int		mLevel;

	float	mExp;
	BarUI*	mExpBar;


public:
	float GetMaxExp() { return 10.f * mLevel + 10.f; };
	float GetExp() { return mExp; };
	void  AddExp(float exp) { mExp += exp; }


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

