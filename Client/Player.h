#pragma once
#include "CObject.h"
#include "AI.h"

class Skill;

struct tUpgrad
{

};


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

	
	Skill* mSkill[(UINT)LEVELUP_EFFECT::END - (UINT)LEVELUP_EFFECT::SKILL_START] = {};
};


class CTexture;
class Gun;
class BarUI;
class CUI;
class LevelupUI;



class Player :
	public CObject
{

private:
	float	mfDelay;
	float	mfCurDelay;

	Vect2	mvDir;

	Gun*	mCurGun;

	int		mLevel;

	float	mExp;
	BarUI*	mExpBar;

	CUI*	mLevelupUI;

	tPlayerInfo			mtPlayerInfo;
	AI<PLAYER_STATE>*	mAI;


public:
	tPlayerInfo GetInfo() { return mtPlayerInfo; }
	void SetInfo(tPlayerInfo _info) { mtPlayerInfo = _info; }

	float GetMaxExp() { return 10.f * mLevel + 10.f; };
	float GetExp() { return mExp; };
	void  AddExp(float exp) { mExp += exp; }

	Vect2 GetRunDir() { return mvDir; }
	Gun* GetCurGun() { return mCurGun; }

	void SetAI(AI<PLAYER_STATE>* pAI) { mAI = pAI; mAI->SetOwner(this); }
	AI<PLAYER_STATE>* GetAI() { return mAI; }


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

