#pragma once
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


public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(T state) : mState(state), mpAI(nullptr) {}
	virtual ~CState() {}

	friend class AI<T>;
};

