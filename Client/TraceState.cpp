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

	//// �÷��̾ ������ �νĹ��� ���η� ����
	if (Vect2::Distance(vPlayerPos, vMonsterPos) < pMonster->GetInfo().atkRange)
	{
		if (pMonster->GetType() == MONSTER_TYPE::LONG)
		{
			if (mAttakDelay > pMonster->GetInfo().atkSpeed)					// ������ ���ݼӵ����� �ð��� �� Ŀ����
			{
				ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);				// ���ݻ��·� ��ȯ
				mAttakDelay = 0.f;											// �����̽ð��� üũ�� ������ ������ ���ݸ���� ��� �ݺ��Ǵ� ���� �����ϱ� ����
			}																// �� �ѹ� �����ϸ� ���� ���ݻ��±��� ���ݸ���� ������ ����
		}
	}
}


void TraceState::Exit()
{
}