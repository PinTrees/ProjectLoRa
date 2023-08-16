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


#define DESTROY_DELAY 18.f

TraceState::TraceState()
	: CState(MONSTER_STATE::TRACE)
	, mAstarDelay(0.75f)
	, mCurDelay(0.f)
	, mvTargetPos(Vect2::zero)
	, mAttakDelay()
	, mCurDestroyDelay(0.f)
{
}


TraceState::~TraceState()
{
}


void TraceState::Enter()
{
	if (mvTargetPos == Vect2::zero)
		mvTargetPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	Monster* pMonster = (Monster*)GetOwner();
	if (pMonster->GetType() == MONSTER_TYPE::ELITE)
		mAstarDelay = 0.2f;
}


void TraceState::Update()
{
	mCurDelay += DT;
	mAttakDelay += DT;
	mCurDestroyDelay += DT;

	Monster* pMonster = (Monster*)GetOwner();
	Vect2 vMonsterPos = pMonster->GetLocalPos();
	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	GetOwner()->GetAnimator()->Play(vMonsterPos.x > vPlayerPos.x ? L"RUN_L" : L"RUN_R", true);

	if (pMonster->GetType() == MONSTER_TYPE::LOCK)
	{
		if (mCurDestroyDelay > DESTROY_DELAY)
		{
			mCurDestroyDelay = 0.f;
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
			return;
		}

		Vect2 vDir = (mvTargetPos - vMonsterPos).Normalize();
		pMonster->SetPos(pMonster->GetPos() + vDir * DT * pMonster->GetInfo().curSpeed);
		return;
	}

	if (mCurDelay > mAstarDelay)
	{
		mCurDelay = 0.f;

		Vect2 vMonPos = pMonster->GetLocalPos() / TILE_SIZE_RENDER;
		Vect2 vTargetPos = PlayerMgr::GetI()->GetPlayer()->GetLocalPos() / TILE_SIZE_RENDER;
		auto tCurFindPathType = SettingMgr::GetI()->GetFindPathType();

		AstarMgr::GetI()->SetStartPos((int)vMonPos.x, (int)vMonPos.y);
		AstarMgr::GetI()->SetTargetPos((int)vTargetPos.x, (int)vTargetPos.y);
		AstarMgr::GetI()->Find();
		vector<Vect2> vecPosList = AstarMgr::GetI()->GetFinalPosList();

		if (vecPosList.size() > 1)
		{
			Vect2 mTileOffet = Vect2(TILE_SIZE_RENDER, TILE_SIZE_RENDER) * 0.5f;

			mvTargetPos = vecPosList[1] * TILE_SIZE_RENDER + mTileOffet;
			pMonster->SetPath(vecPosList);
		}

		vecPosList.clear();
	}

	if (Vect2::Distance(vMonsterPos, mvTargetPos) < 5.f)
		return;

	Vect2 dir = (mvTargetPos - vMonsterPos).Normalize();
	GetOwner()->SetPos(pMonster->GetPos() + dir * pMonster->GetInfo().curSpeed * DT);

	if (pMonster->GetFreeze() || pMonster->GetType() != MONSTER_TYPE::LONG)
		return;

	//// 플레이어가 몬스터의 인식범위 내부로 진입
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().atkRange)
	{
		if (mAttakDelay > pMonster->GetInfo().atkSpeed)					// 몬스터의 공격속도보다 시간이 더 커지면
		{
			mAttakDelay = 0.f;											// 딜레이시간을 체크한 이유는 몬스터의 공격모션이 계속 반복되는 것을 방지하기 위함
			ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);				// 공격상태로 전환
		}
	}
}


void TraceState::Exit()
{
}