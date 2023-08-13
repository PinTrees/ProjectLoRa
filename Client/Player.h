#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	fullHP = 100.f;				// 최대체력
	float	curHp = 0.f;				// 체력
	float	fullMP = 100.f;				// 최대마나
	float	curMP = 100.f;				// 마나
	float	regenerationHP = 0.f;		// 체력재생
	float	moveSpeed = 300.f;			// 이동 속도
	float	atkDamage = 20.f;			// 공격력
	float	atkSpeed = 10.f;			// 공격스피드
	float	atkRange = 500.f;			// 사거리
	float	shotSpeed = 100.f;			// 총알 속도
	float	reloadSpeed = 50.f;			// 장전속도
	float	shotAngle = 0.f;			// 발사 각도(명중률)
	float	shotCount = 1.f;			// 발사 총알 개수


	float   atkDelay = 0.75f;


	UINT	penetration = 0;			// 관통 수
	UINT	splitCount = 0;				// 분열 수
	UINT	bounceCount = 0;			// 튕김 수
};


class CTexture;
class Skill;
class BarUI;
class CImageUI;
class LevelupUI;
class CSound;
class TextUI;


class Player :
	public CObject
{

private:
	float	mfDelay;
	float	mfCurDelay;
	float	mMpDelay;
	Vect2	mvDir;

	int			mLevel;
	float		mExp;
	BarUI*		mExpBar;
	BarUI*		mMpBar;
	CImageUI*	mHpBar;
	TextUI*		mHpText;

	tPlayerInfo			mtInfo;
	vector<Skill*>		mVecSkill;
	vector<SKILL_TYPE>	mVecMaxLevelSkill;
	AI<PLAYER_STATE>*	mAI;

	CSound* mpCoinSound;
	CSound* mpLevelUpSound;


public:
	tPlayerInfo& GetInfo() { return mtInfo; }
	vector<SKILL_TYPE>& GetMaxLevelSkill() { return mVecMaxLevelSkill; }
	void SetInfo(tPlayerInfo _info) { mtInfo = _info; }

	float GetMaxExp() { return 2.f * mLevel + 5.f; };
	float GetExp() { return mExp; };
	void  AddExp(float exp) { mExp += exp; }

	Vect2 GetRunDir() { return mvDir; }

	void SetAI(AI<PLAYER_STATE>* pAI) { mAI = pAI; mAI->SetOwner(this); }
	AI<PLAYER_STATE>* GetAI() { return mAI; }


public:
	Skill* FindSkill(SKILL_TYPE type);
	void AddSkill(Skill* _skill);
	void UseSkill();
	void AddDamage(float _damage) { mtInfo.curHp -= _damage; }
	const vector<Skill*>& GetSkillList() { return mVecSkill; };


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionStay(CCollider* _pOther) {}		// In Collision
	virtual void OnCollisionExit(CCollider* _pOther) {}		// Exit Collision


private:
	void calExp();

	CLONE(Player);


public:
	Player();
	virtual ~Player() override;

	friend class LevelupUI;
};

