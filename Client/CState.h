#pragma once
<<<<<<< Updated upstream


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
=======
#include "AI.h"

class CObject;

template <typename T>
class AI;



template <typename T>
class CState
{
private:
	AI<T>*			mpAI;
	T				mState;


public:
	AI<T>* GetAI() { return mpAI; }
	T GetType() { return mState; }

	CObject* GetOwner() { return mpAI->GetOwner(); }

>>>>>>> Stashed changes

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
<<<<<<< Updated upstream
	CState(MONSTER_STATE state);
	virtual ~CState();

	friend class AI;
=======
	CState(T state)
		: mState(state)
		, mpAI(nullptr)
	{}
	virtual ~CState()	{}


	friend class AI<T>;
>>>>>>> Stashed changes
};

