#pragma once
#include "CObject.h"
#include "AI.h"

struct tMonsterInfo
{
	wstring		UID;
	float		speed;			// �̵��ӵ�
	float		hp;				// ü��
	float		recogRange;		// ��������
	float		atkRange;		// ���ݰŸ�
	float		atk;			// ���ݷ�

	float		curHp;
};


class MonsterFactory;
class BarUI;



class Monster :
	public CObject
{
private:
	tMonsterInfo		mtInfo;
	AI<MONSTER_STATE>* mAI;

	BarUI* mHpBar;

	vector<Vect2>		mPath;

public:
	float GetSpeed() { return mtInfo.speed; }
	void SetSpeed(float _fspeed) { mtInfo.speed = _fspeed; }

	const tMonsterInfo GetInfo() { return mtInfo; }

	void SetAI(AI<MONSTER_STATE>* pAI);
	void SetPath(vector<Vect2>& path) { mPath = path; };

	void AddDamage(float damage);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnDestroy() override;

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Monster);


private:
	void setMonsterInfo(const tMonsterInfo& info) { mtInfo = info; }


public:
	Monster(const wstring& uid);
	~Monster();

	friend class MonsterFactory;
};

