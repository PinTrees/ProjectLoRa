#include "pch.h"	
#include "AI.h"

#include "CState.h"

AI::AI()
	:mpCurstate(nullptr)
	, mpOwner(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(mMapState);
}


void AI::Update()
{
	mpCurstate->Update();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);

	mMapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->mpAI = this;
	
}

CState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = mMapState.find(_eState);
	if (iter == mMapState.end())
		return nullptr;

	return iter->second;
}

void AI::SetCurState(MON_STATE _eState)
{

	mpCurstate =GetState(_eState);
	assert(mpCurstate);

}

void AI::ChangeState(MON_STATE _eNextState)
{
	CState* pNextState = GetState(_eNextState);

	assert(pNextState != mpCurstate);

	mpCurstate->Exit();
	mpCurstate = pNextState;

	mpCurstate->Enter();

}
