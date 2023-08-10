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
	, mAstarDelay(0.5f)
	, mCurDelay(0.f)
	, mvTargetPos(Vect2::zero)
	, mAttakDelay()
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
	mAttakDelay += DT;

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

		Vect2 vMonPos = pMonster->GetLocalPos() / TILE_SIZE_RENDER;
		Vect2 vTargetPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos() / TILE_SIZE_RENDER;

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

	Vect2 vMonsterPos = pMonster->GetLocalPos();
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	if (Vect2::Distance(vMonsterPos, mvTargetPos) < 5.f)
		return;

	Vect2 dir = mvTargetPos - vMonsterPos;
	dir.Normalize();
	GetOwner()->SetPos(pMonster->GetPos() + dir * pMonster->GetInfo().speed * DT);

	//// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().atkRange)
	{
		if (pMonster->GetType() == MONSTER_TYPE::LONG)
		{
			if (mAttakDelay > pMonster->GetInfo().atkSpeed)					// 몬스터의 공격속도보다 시간이 더 커지면
			{
				ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);				// 공격상태로 전환
				mAttakDelay = 0.f;											// 딜레이시간을 체크한 이유는 몬스터의 공격모션이 계속 반복되는 것을 방지하기 위함
			}																// 즉 한번 공격하면 다음 공격상태까지 공격모션을 취하지 않음
		}
	}
}


void TraceState::Exit()
{
}