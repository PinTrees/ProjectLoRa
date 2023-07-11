#pragma once


class AI;
class CMonster;

class CState
{
private:
	AI*				mpAI;
	MONSTER_STATE	mState;

public:
	AI* GetAI() { return mpAI; }
	MONSTER_STATE GetType() { return mState; }

	CMonster* GetMonster();

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(MONSTER_STATE state);
	virtual ~CState();

	friend class AI;
};

