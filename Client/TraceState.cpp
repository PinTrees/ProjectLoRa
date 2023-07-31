#include "pch.h"
#include "TraceState.h"

// System Manager Header
#include "CTimeMgr.h"

// Manager Header
#include "PlayerMgr.h"
#include "AstarMgr.h"
#include "JPSMgr.h"

// GameObject Header
#include "Player.h"
#include "Monster.h"

// Components Header
#include "CAnimator.h"

#include "SettingMgr.h"
 


TraceState::TraceState()
	: CState(MONSTER_STATE::TRACE)
	, mAstarDelay(0.3f)
	, mCurDelay(0.f)
	, mvTargetPos(Vect2::zero)
{
}


TraceState::~TraceState()
{
}


void TraceState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"RUN", true);
}


void TraceState::Update()
{
	mCurDelay += DT;

	Monster* pMonster = (Monster*)GetOwner();

	if (pMonster->GetInfo().curHp <= 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		return;
	}

	vector<Vect2> vecPosList;

	if (mCurDelay > mAstarDelay)
	{
		mCurDelay = 0.f;

		Vect2 vMonPos = pMonster->GetPos() / TILE_SIZE_RENDER;
		Vect2 vTargetPos = PlayerMgr::GetI()->GetPlayer()->GetPos() / TILE_SIZE_RENDER;

		auto tCurFindPathType = SettingMgr::GetI()->GetFindPathType();

		if (tCurFindPathType == FIND_PATH_TYPE::ASTAR)
		{
			AstarMgr::GetI()->SetStartPos((int)vMonPos.x, (int)vMonPos.y);
			AstarMgr::GetI()->SetTargetPos((int)vTargetPos.x, (int)vTargetPos.y);
			AstarMgr::GetI()->Find();
			vecPosList = AstarMgr::GetI()->GetFinalPosList();
		}
		else if (tCurFindPathType == FIND_PATH_TYPE::JPS_B)
		{
			JPSMgr::GetI()->SetStartPos(vMonPos.x, vMonPos.y);
			JPSMgr::GetI()->SetTargetPos(vTargetPos.x, vTargetPos.y);
			JPSMgr::GetI()->Find();
			vecPosList = JPSMgr::GetI()->GetFinalPosList();
		}

		if (vecPosList.size() > 1)
		{
			Vect2 mTileOffet = Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER) * 0.5f;

			mvTargetPos = vecPosList[1] * TILE_SIZE_RENDER + mTileOffet;
			pMonster->SetPath(vecPosList);
		}
	}

	Vect2 vMonsterPos = pMonster->GetPos();

	if (Vect2::Distance(vMonsterPos, mvTargetPos) < 5.f)
		return;

	Vect2 dir = mvTargetPos - vMonsterPos;
	dir.Normalize();
	GetOwner()->SetPos(vMonsterPos + dir * 75.f * DT);

	//// 플레이어가 몬스터의 인식범위 내부로 진입
	//if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().atkRange)
	//{
	//	ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
	//}
}


void TraceState::Exit()
{
}