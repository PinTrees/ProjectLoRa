#include "pch.h"

#include "BSkillAtkState.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "CTimeMgr.h"

#include "Random.h"

// Components Header
#include "CAnimator.h"
#include "CAnimation.h"


#include "Monster.h"
#include "Stone.h"

#include "CTimeMgr.h"


BSkillAtkState::BSkillAtkState()
	: CState(MONSTER_STATE::SKILLATK)
	, mAtkDelay(4.f)
	, mCurDelay(0.f)
{
}

BSkillAtkState::~BSkillAtkState()
{
	
}


void BSkillAtkState::Enter()
{
	mCurDelay = 0.f;

	Vect2 vBoss = GetOwner()->GetLocalPos();
	Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	GetOwner()->GetAnimator()->Play(vBoss.x > vPlayer.x ? L"ATK_L" : L"ATK_R", false);

	float curv_x = (vPlayer.x - vBoss.x) / 2.f;			// 몬스터와 플레이어의 중간거리를 구한다.
	float curv_y = (vPlayer.y - vBoss.y) / 2.f - 500.f;	// 수류탄이 높게 뜬 후 떨어지게 하기위해 추가로 500.f 를 감소시킨다.

	Vect2 curvPoint;

	curvPoint.x = vBoss.x + curv_x;		// 커브 지점의 좌표를 찍는다.
	curvPoint.y = vBoss.y + curv_y;

	for (size_t i = 0; i < 8; i++)
	{
		Stone* stone = new Stone;

		int targetX = CRandom::GetI()->Next(vPlayer.x - 300, vPlayer.x + 300);
		int targetY = CRandom::GetI()->Next(vPlayer.y - 300, vPlayer.y + 300);

		stone->SetStartPoint(vBoss);
		stone->SetCurvePoint(curvPoint);
		stone->SetTargetPoint(Vect2(targetX, targetY));
		stone->SetPos(vBoss);
		CreateObject(stone, GROUP_TYPE::DEFAULT); // 해당오브젝트와는 충돌처리로 하지않고 좌표로 확인함
	}
}

void BSkillAtkState::Update()
{
	/*mCurDelay += DT;
	if (mCurDelay > mAtkDelay)
	{
		mCurDelay = 0.f;
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}*/

	if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}
}

void BSkillAtkState::Exit()
{

}
