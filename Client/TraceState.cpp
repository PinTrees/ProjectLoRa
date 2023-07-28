#include "pch.h"
#include "TraceState.h"

// System Manager Header
#include "CTimeMgr.h"

// GameMgr
#include "AstarMgr.h"
#include "PlayerMgr.h"

// GameObject Header
#include "Player.h"
#include "Monster.h"

// Components Header
#include "CAnimator.h"




TraceState::TraceState()
    : CState(MONSTER_STATE::TRACE)
    , mAstarDelay(0.2f)
    , mCurDelay(0.f)
{
}


TraceState::~TraceState()
{
}


void TraceState::Enter()
{
    GetOwner()->GetAnimator()->Play(L"RUN", true);
}

void TraceState::Update() {
    mCurDelay += DT;

    Monster* monster = (Monster*)GetOwner();

    if (monster->GetInfo().curHp <= 0) {
        ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
        return;
    }


    Vect2 vMonsterPos = GetOwner()->GetPos();
    Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();


    // 일정 주기마다 경로 탐색을 수행
    if (mCurDelay > mAstarDelay) {
        mCurDelay = 0.0f;
        int monsterX = monster->GetPos().x / TILE_SIZE_RENDER;
        int monsterY = monster->GetPos().y / TILE_SIZE_RENDER;
        vector<Vect2> path = AstarMgr::GetI()->AstarCall(monsterX, monsterY);
        ((Monster*)GetOwner())->SetPath(path);

        // 경로 탐색 결과를 사용하여 몬스터를 이동시키는 로직 구현
        if (path.size() > 1)
        {
            path.erase(path.begin());
            mTargetPath = path[0];
        }
        else
        {
            mTargetPath = vMonsterPos;
        }
    }

    if (Vect2::Distance(vMonsterPos, mTargetPath) < 5.f)
        return;

    Vect2 dir = mTargetPath - vMonsterPos;
    dir.Normalize();
    GetOwner()->SetPos(vMonsterPos + dir * 100.f * DT);


}

void TraceState::Exit()
{

}