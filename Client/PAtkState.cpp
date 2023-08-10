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
	vector<CObject*> vecMon = pScene->GetGroupObject(GROUP_TYPE::MONSTER);

	if (vecMon.empty()) return;

	float length = 1000.f;
	Vect2 monsterPos;
	Vect2 vDir;
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		float fDistance = Vect2::Distance(vecMon[i]->GetLocalPos(), vPlayerLocalPos);
		if (fDistance < length)	// �÷��̾�� ������ ���̰� length ���� ���� �� (���� ����� ���� ã�´�)
		{
			length = fDistance;
			vDir = vecMon[i]->GetLocalPos() - vPlayerLocalPos;
		}
	}

	vDir.Normalize();

	pPlayer->GetAnimator()->Play(monsterPos.x > vPlayerPos.x ? L"ATK_R" : L"ATK_L", true);

	for (int i = 0; i < 5; ++i)
	{
		// ���� �߻簢 ���� ���� ������ ������ �����մϴ�.
		int shotAngle = 30 * 0.5f;
		float angle = vDir.ToAngle() + (float)CRandom::GetI()->Next(shotAngle * -1, shotAngle); // ������ ����
		Vect2 vDir = Vect2::FromAngle(angle);

		// �Ѿ� ������Ʈ
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

