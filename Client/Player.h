#pragma once
#include "CObject.h"
#include "AI.h"



struct tPlayerInfo
{
	float	fullHP = 100.f;				// �ִ�ü��
	float	curHp = 0.f;				// ü��
	float	fullMP = 100.f;				// �ִ븶��
	float	curMP = 100.f;				// ����
	float	regenerationHP = 0.f;		// ü�����
	float	moveSpeed = 300.f;			// �̵� �ӵ�
	float	atkDamage = 20.f;			// ���ݷ�
	float	atkSpeed = 10.f;			// ���ݽ��ǵ�
	float	atkRange = 500.f;			// ��Ÿ�
	float	shotSpeed = 100.f;			// �Ѿ� �ӵ�
	float	reloadSpeed = 50.f;			// �����ӵ�
	float	shotAngle = 0.f;			// �߻� ����(���߷�)
	float	shotCount = 1.f;			// �߻� �Ѿ� ����


	float   atkDelay = 0.75f;


	UINT	penetration = 0;			// ���� ��
	UINT	splitCount = 0;				// �п� ��
	UINT	bounceCount = 0;			// ƨ�� ��
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

