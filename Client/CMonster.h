#pragma once
#include "CObject.h"


struct tMonsterInfo
{
	float		speed;			// �̵��ӵ�
	float		hp;				// ü��
	float		recogRange;		// ��������
	float		atkRange;		// ���ݰŸ�
	float		atk;			// ���ݷ�

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

