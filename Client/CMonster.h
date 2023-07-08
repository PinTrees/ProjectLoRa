#pragma once
#include "CObject.h"

struct tMonInfo
{
	float		mfHp;				// ü��
	float       mfSpeed;			// �ӵ�
	float		mfDetectRange;		// ���� ����
	float		mfAttRange;			// ���� ����
	float		mfAtt;				// ���ݷ�

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

