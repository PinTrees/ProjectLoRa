#include "pch.h"
#include "AI.h"

#include "CState.h"
#include "IdleState.h"
#include "TraceState.h"



AI::AI()
	: mCurState(nullptr)
	, mOwner(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(mMapState);
}




void AI::AddState(CState* pState)
{
	CState* state = GetState(pState->GetType());
	if (nullptr != state)
		return;

	mMapState.insert(make_pair(pState->GetType(), pState));
	pState->mpAI = this;
}


CState* AI::GetState(MONSTER_STATE key)
{
	map<MONSTER_STATE, CState*>::iterator iter = mMapState.find(key);

	if (iter == mMapState.end())
		return nullptr;

	return iter->second;
}

void AI::ChangeState(MONSTER_STATE nextState)
{
	CState* pNextState = GetState(nextState);
	assert(pNextState != mCurState);

	mCurState->Exit();
	mCurState = pNextState;
	mCurState->Enter();
}

void AI::SetCurState(MONSTER_STATE target)
{
	mCurState = GetState(target);
	//assert(!mCurState);
}


void AI::Update()
{
	if (nullptr != mCurState)
	{
		mCurState->Update();
	}
}	

