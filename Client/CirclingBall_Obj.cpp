#include "pch.h"
#include "CirclingBall_Obj.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "PlayerMgr.h"

#include "Player.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "Skill.h"

CirclingBall_Obj::CirclingBall_Obj()
	: mTheta()
	, mPrevLv()
{
	SetMaxDelay(0.f);		// 스킬 지속시간이 필요 없기 때문에 0으로 세팅
	SetDamageDelay(0.2f);	// ~초마다 데미지를 입힘
	SetName(L"CirclingBall");
	SetDamage(7.f);

	CreateAnimator();
	CreateCollider();
	
	GetCollider()->SetScale(Vect2(40.f, 40.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 18.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"CirclingBall", L"texture\\effect\\12.bmp");
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(63.f, 75.f), Vect2(63.f, 0.f), 0.07f, 6);
	SetScale(Vect2(63.f, 75.f) * 1.2f);

	GetAnimator()->Play(L"IDLE", true);
}

CirclingBall_Obj::~CirclingBall_Obj()
{
}

void CirclingBall_Obj::Update()
{
	if (mPrevLv < GetOwner()->GetSkillLevel())		// 이전 스킬 레벨과 비교한다.
	{												// 스킬 레벨이 오르면 공이 없어지게 한다. (개수에 맞춰서 다시 생성하기 때문)
		DeleteObject(this);
		return;
	}

	Vect2 vPlayer = PlayerMgr::GetI()->GetPlayer()->GetLocalPos();

	Vect2 vPos;
	vPos.x = cosf(mTheta) * (100.f + 15.f * GetOwner()->GetSkillLevel());
	vPos.y = sinf(mTheta) * (100.f + 15.f * GetOwner()->GetSkillLevel());

	SetPos(vPos + vPlayer);			// 공이 플레이어 주변을 빙글빙글 돌도록 세팅한다.
	GetAnimator()->Update();

	mTheta += 1.5f * DT;

	if (mTheta >= 360.f)		// Theta 값이 너무 커지지 않도록 함
		mTheta = 0.f;
}

void CirclingBall_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
