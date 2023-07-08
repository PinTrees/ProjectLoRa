#pragma once


class CMonster;
class CState;

class AI
{
private:
	map<MONSTER_STATE, CState*>	mMapState;
	CState*						mCurState;
		
	CMonster*				mOwner;


public:
	void AddState(CState* pState);
	CState* GetState(MONSTER_STATE key);

	void SetCurState(MONSTER_STATE target);


public:
	void Update();


public:
	AI();
	~AI();

	friend class CMonster;
};

