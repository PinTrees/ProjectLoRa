#include "pch.h"

#include "SkillAtkState.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "CTimeMgr.h"

#include "Random.h"

// Components Header
#include "CAnimator.h"
#include "CAnimation.h"


#include "Monster.h"

#include "Stone.h"

SkillAtkState::SkillAtkState()
	: CState(MONSTER_STATE::SKILLATK)
{
}

SkillAtkState::~SkillAtkState()
{
}

void SkillAtkState::Update()
{

		Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetPos();

		Vect2 vBoss = GetOwner()->GetPos();


		float curv_x = (vPlayer.x - vBoss.x) / 2.f;			// ���Ϳ� �÷��̾��� �߰��Ÿ��� ���Ѵ�.
		float curv_y = (vPlayer.y - vBoss.y) / 2.f - 1000.f;	// ����ź�� ���� �� �� �������� �ϱ����� �߰��� 500.f �� ���ҽ�Ų��.

		Vect2 curvPoint;

		curvPoint.x = vBoss.x + curv_x;		// Ŀ�� ������ ��ǥ�� ��´�.
		curvPoint.y = vBoss.y + curv_y;

		for (size_t i = 0; i < 8; i++)
		{
			Stone* stone = new Stone;

			int targetX = CRandom::GetI()->Next(vPlayer.x-300, vPlayer.x+ 300);
			int targetY = CRandom::GetI()->Next(vPlayer.y- 300, vPlayer.y + 300);


			stone->SetStartPoint(vBoss);
			stone->SetCurvePoint(curvPoint);
			stone->SetTargetPoint(Vect2(targetX, targetY));
			stone->SetPos(vBoss);
			CreateObject(stone, GROUP_TYPE::DEFAULT); // �ش������Ʈ�ʹ� �浹ó���� �����ʰ� ��ǥ�� Ȯ����
		}

	ChangeAIState(GetAI(), MONSTER_STATE::TRACE);

	//if (GetOwner()->GetAnimator()->GetCurAnimation()->IsFinish())
	//{
	// ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	//	//mAtkAvailable = true;
	//}

}

void SkillAtkState::Enter()
{
	GetOwner()->GetAnimator()->Play(L"ATK", false);
}

void SkillAtkState::Exit()
{

}

