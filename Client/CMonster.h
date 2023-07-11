#pragma once
#include "CObject.h"


struct tMonsterInfo
{
	float		speed;			// 이동속도
	float		hp;				// 체력
	float		recogRange;		// 인지범위
	float		atkRange;		// 공격거리
	float		atk;			// 공격력

	float		curHp;
};

class AI;
class MonsterFactory;
class BarUI;



class CMonster :
	public CObject
{
private:
	tMonsterInfo	mtInfo;
	AI*				mAI;

	BarUI*			mHpBar;


public:
	float GetSpeed() { return mtInfo.speed; }
	void SetSpeed(float _fspeed) { mtInfo.speed = _fspeed; }

	const tMonsterInfo GetInfo() { return mtInfo; }

	void SetAI(AI* pAI);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnDestroy() override;

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(CMonster);


private:
	void setMonsterInfo(const tMonsterInfo& info) { mtInfo = info; }


public:
	CMonster();
	~CMonster();

	// Inherited via CObject
	friend class MonsterFactory;
};

