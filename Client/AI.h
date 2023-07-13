#pragma once
<<<<<<< Updated upstream


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
	void ChangeState(MONSTER_STATE nextState);

	CMonster* GetOwner() { return mOwner; }	

	void SetCurState(MONSTER_STATE target);


public:
	void Update();


public:
	AI();
	~AI();

	friend class CMonster;
=======
#include "CState.h"


class CObject;
class Monster;

template <typename T>
class CState;




template <typename T>
class AI
{
private:
	map<T, CState<T>*>		mMapState;
	CState<T>*				mCurState;
		
	CObject*				mOwner;


public:
	void SetOwner(CObject* owner) { mOwner = owner; }
	CObject* GetOwner() { return mOwner; }

	void AddState(CState<T>* pState)
	{
		CState<T>* state = GetState(pState->GetType());
		if (nullptr != state)
			return;

		mMapState.insert(make_pair(pState->GetType(), pState));
		pState->mpAI = this;
	}

	CState<T>* GetState(T key)
	{
		typename map<T, CState<T>*>::iterator iter = mMapState.find(key);

		if (iter == mMapState.end())
			return nullptr;

		return iter->second;
	}

	void ChangeState(T nextState)
	{
		CState<T>* pNextState = GetState(nextState);
		assert(pNextState != mCurState);

		mCurState->Exit();
		mCurState = pNextState;
		mCurState->Enter();
	}

	void SetCurState(T target)
	{
		mCurState = GetState(target);
		//assert(!mCurState);
	}


public:
	void Update()
	{
		if (nullptr != mCurState)
		{
			mCurState->Update();
		}
	}


public:
	AI()
		: mCurState(nullptr)
		, mOwner(nullptr)
	{
	}
	~AI() 
	{
		Safe_Delete_Map(mMapState);
	}

	friend class CObject;
>>>>>>> Stashed changes
};

