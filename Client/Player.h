#pragma once
#include "CObject.h"
#include "AI.h"



struct tUpgrad
{

};


class CTexture;
class Gun;
class BarUI;
class CUI;




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

	CUI*	mLevelupUI;
	AI<PLAYER_STATE>* mAI;


public:
	void SelectLevelUp(DWORD_PTR param);


public:
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

