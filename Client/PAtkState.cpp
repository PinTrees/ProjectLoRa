#include "pch.h"
#include "PAtkState.h"

#include "CKeyMgr.h"
#include "Player.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "Random.h"
#include "Bullet.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"


PAtkState::PAtkState()
	: CState(PLAYER_STATE::ATTACK)
	, mCurDelay(0.f)
	, mAtkDelay(0.f)
{
}

PAtkState::~PAtkState()
{
}



void PAtkState::Enter()
{
	Player* pPlayer = (Player*)GetOwner();
	Vect2 vPlayerPos = pPlayer->GetPos();
	Vect2 vPlayerLocalPos = pPlayer->GetLocalPos();

	CScene* pScene = CSceneMgr::GetI()->GetCurScene();
	const vector<CObject*>& vecMon = pScene->GetGroupObject(GROUP_TYPE::MONSTER);
	const vector<CObject*>& vecBoss = pScene->GetGroupObject(GROUP_TYPE::BOSS);

	Vect2 vDir;
	Vect2 monsterPos;

	if (vecMon.size() > 0)
	{
		float length = 1000.f;
		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			float fDistance = Vect2::Distance(vecMon[i]->GetLocalPos(), vPlayerLocalPos);
			if (fDistance < length)	// 플레이어와 몬스터의 길이가 length 보다 작을 때 (가장 가까운 적을 찾는다)
			{
				length = fDistance;
				vDir = vecMon[i]->GetLocalPos() - vPlayerLocalPos;
			}
		}
		vDir.Normalize();
	}
	else if (vecBoss.size() > 0)
	{
		monsterPos = vecBoss[0]->GetLocalPos();
		vDir = vecBoss[0]->GetLocalPos() - vPlayerLocalPos;
	}

	//pPlayer->GetAnimator()->Play(monsterPos.x > vPlayerPos.x ? L"ATK_R" : L"ATK_L", true);

	for (int i = 0; i < 3; ++i)
	{
		// 일정 발사각 범위 내의 랜덤한 방향을 생성합니다.
		int shotAngle = 15 * 0.5f;
		float angle = vDir.ToAngle() + (float)CRandom::GetI()->Next(shotAngle * -1, shotAngle); // 랜덤한 각도
		Vect2 vDir = Vect2::FromAngle(angle);

		// 총알 오브젝트
		tBullet bInfo = {};
		bInfo.damage = pPlayer->GetInfo().atkDamage;
		bInfo.bounceCount = 0;
		bInfo.penetrationCount = 0;
		bInfo.splitCount = 0;

		Bullet* pBullet = new Bullet(L"1");
		pBullet->SetPos(vPlayerPos + vDir.Normalize() * 35.f);
		pBullet->SetDir(vDir);
		pBullet->SetInfo(bInfo);
		pBullet->SetName(L"Missile_Player");

		CreateObject(pBullet, GROUP_TYPE::PROJ_PLAYER);
	}

	mAtkDelay = pPlayer->GetInfo().atkDelay;
	mCurDelay = 0.f;
}

void PAtkState::Update()
{
	mCurDelay += DT;

	if (mCurDelay > mAtkDelay) {
		mCurDelay = 0.f;
		Player* pPlayer = (Player*)GetOwner();
		ChangeAIState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void PAtkState::Exit()
{
}

