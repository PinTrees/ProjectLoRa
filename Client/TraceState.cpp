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
	, mAstarDelay(1.f)
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


    Vect2 vMonsterPos = GetOwner()->GetLocalPos();
    Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();
    // ���� �ֱ⸶�� ��� Ž���� ����
    if (mCurDelay > mAstarDelay) {
        mCurDelay = 0.0f;
        int monsterX = monster->GetPos().x / TILE_SIZE_RENDER;
        int monsterY = monster->GetPos().y / TILE_SIZE_RENDER;
        vector<Vect2*> path = AstarMgr::GetI()->AstarCall(monsterX, monsterY);
        vector<Vect2*>::iterator iter = path.begin();
        ((Monster*)GetOwner())->SetPath(path);

       
        // ��� Ž�� ����� ����Ͽ� ���͸� �̵���Ű�� ���� ����
        if (!path.empty())
        {
            path.erase(iter);
            if (path.empty())
            {
                GetOwner()->SetPos(vPlayerPos);
            }
            else
            {
                GetOwner()->SetPos((*path[0]));

            }
        }
    }
    
}

void TraceState::Exit()
{

}