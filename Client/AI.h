#pragma once


class CObject;
class Monster;
class CState;

class AI
{
private:
	map<MONSTER_STATE, CState*>	mMapState;
	CState*						mCurState;
		
	CObject*				mOwner;


public:
	void AddState(CState* pState);
	CState* GetState(MONSTER_STATE key);
	void ChangeState(MONSTER_STATE nextState);

	void SetOwner(CObject* owner) { mOwner = owner; }
	CObject* GetOwner() { return mOwner; }

	void SetCurState(MONSTER_STATE target);


public:
	void Update();


public:
	AI();
	~AI();

	friend class CObject;
};

