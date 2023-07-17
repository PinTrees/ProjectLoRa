#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	fullHP = 100.f;				// �ִ�ü��
	float	curHp = 0.f;				// ü��
	float	regenerationHP = 0.f;		// ü�����
	float	moveSpeed = 300.f;			// �̵� �ӵ�
	float	atkDamage = 10.f;			// ���ݷ�
	float	atkSpeed = 10.f;			// ���ݽ��ǵ�
	float	atkRange = 500.f;			// ��Ÿ�
	float	shotSpeed = 100.f;			// �Ѿ� �ӵ�
	float	reloadSpeed = 50.f;			// �����ӵ�
	float	shotAngle = 0.f;			// �߻� ����(���߷�)
	float	shotCount = 1.f;			// �߻� �Ѿ� ����

	UINT	penetration = 0;			// ���� ��
	UINT	splitCount = 0;				// �п� ��
	UINT	bounceCount = 0;			// ƨ�� ��
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

