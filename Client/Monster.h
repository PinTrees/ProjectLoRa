#pragma once
#include "CObject.h"
#include "AI.h"

struct tMonsterInfo
{
	wstring		UID;
	float		speed;			// 이동속도
	float		hp;				// 체력
	float		recogRange;		// 인지범위
	float		atkRange;		// 공격거리
	float		atk;			// 공격력
	float		atkSpeed;		// 공격속도

	float		curHp;
};


class MonsterFactory;
class BarUI;
class CSound;
class CTexture;


class Monster :
	public CObject
{
protected:
	tMonsterInfo		mtInfo;

private:
	MONSTER_TYPE		mType;
	AI<MONSTER_STATE>*	mAI;

	BarUI* mHpBar;

	vector<Vect2>	mVecPathPos;

	float			mCurDamageDelay;

	CSound*			mHitSound;
	CTexture*		mpShadowTex;
	Vect2	mvShadowOffset;
	Vect2	mvShadowScale;


public:
	MONSTER_TYPE GetType() { return mType; }

	float GetSpeed() { return mtInfo.speed; }
	void SetSpeed(float _fspeed) { mtInfo.speed = _fspeed; }

	const tMonsterInfo& GetInfo() { return mtInfo; }

	void SetAI(AI<MONSTER_STATE>* pAI);

	void AddDamage(float damage);
	void SetPath(vector<Vect2>& vecPos)
	{
		mVecPathPos.clear();

		Vect2 mTileOffet = Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER) * 0.5f;

		for (int i = 0; i < vecPos.size(); ++i)
		{
			mVecPathPos.push_back(vecPos[i] * TILE_SIZE_RENDER + mTileOffet);
		}
	}


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionStay(CCollider* _pOther) override;
	virtual void OnDestroy() override;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Monster);


private:
	void setMonsterInfo(const tMonsterInfo& info) { mtInfo = info; }


public:
	Monster(MONSTER_TYPE mType, const wstring& uid);
	virtual ~Monster() override;

	friend class MonsterFactory;
};

