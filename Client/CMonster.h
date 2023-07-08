#pragma once
#include "CObject.h"

struct tMonInfo
{
	float		mfHp;				// 체력
	float       mfSpeed;			// 속도
	float		mfDetectRange;		// 인지 범위
	float		mfAttRange;			// 공격 범위
	float		mfAtt;				// 공격력

};



class AI;

class CMonster :
	public CObject
{
private:
	tMonInfo mtInfo;
	AI* mpAI;



public:
	float GetSpeed() { return mtInfo.mfSpeed; }
	void SetSpeed(float _fspeed) { mtInfo.mfSpeed = _fspeed; }

	void SetAI(AI* _ai);
	const tMonInfo& GetInfo() { return mtInfo; }

private:
	void SetMonInfo(const tMonInfo& _info) { mtInfo = _info; }



public:

	virtual void OnCollisionEnter(CCollider* _pOther) override;
public:
	virtual void Update() override;
	CLONE(CMonster);


public:
	CMonster();
	~CMonster();

	friend class CMonFactory;
};

