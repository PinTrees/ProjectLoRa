#pragma once
#include "CObject.h"


struct tMonsterInfo
{
	float		speed;			// 이동속도
	float		hp;				// 체력
	float		recogRange;		// 인지범위
	float		atkRange;		// 공격거리
	float		atk;			// 공격력
};

class AI;
class MonsterFactory;




class CMonster :
	public CObject
{
private:
	tMonsterInfo	mtInfo;
	AI*				mAI;

	int				m_iDir;	//1,-1

	CObject*		mpTarget;


public:
	float GetSpeed() { return mtInfo.speed; }
	void SetSpeed(float _fspeed) { mtInfo.speed = _fspeed; }
	void SetTarget(CObject* _object) { mpTarget = _object; }

	void SetAI(AI* pAI);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(CMonster);


private:
	void death();
	void attack();

	void setMonsterInfo(const tMonsterInfo& info) { mtInfo = info; }

public:
	CMonster();
	~CMonster();

	// Inherited via CObject
	friend class MonsterFactory;
};

