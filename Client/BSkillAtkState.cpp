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

	float curv_x = (vPlayer.x - vBoss.x) / 2.f;			// ���Ϳ� �÷��̾��� �߰��Ÿ��� ���Ѵ�.
	float curv_y = (vPlayer.y - vBoss.y) / 2.f - 500.f;	// ����ź�� ���� �� �� �������� �ϱ����� �߰��� 500.f �� ���ҽ�Ų��.

	Vect2 curvPoint;

	curvPoint.x = vBoss.x + curv_x;		// Ŀ�� ������ ��ǥ�� ��´�.
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
		CreateObject(stone, GROUP_TYPE::DEFAULT); // �ش������Ʈ�ʹ� �浹ó���� �����ʰ� ��ǥ�� Ȯ����
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
