#include "pch.h"
#include "Grenade_Obj.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "Grenade_Bomb.h"

Grenade_Obj::Grenade_Obj()
	: mCurTime()
	, mArrivalTime(2.f)
	, mRemainTime()
{
	SetMaxDelay(1.f);
	SetName(L"Grenade");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Grenade", L"texture\\effect\\2.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Grenade", pTex, Vect2(40.f, 0.f), Vect2(40.f, 52.f), Vect2(40.f, 0.f), 0.5f, 1);
	SetScale(Vect2(50.f, 50.f));

	GetAnimator()->Play(L"Grenade", true);
}

Grenade_Obj::~Grenade_Obj()
{
}

void Grenade_Obj::Update()
{
	if (mCurTime > GetMaxDelay())				// 지정한 시간이 지나면
	{
		Grenade_Bomb* bomb = new Grenade_Bomb;	// 폭발오브젝트를 생성한다.
		bomb->SetPos(Vect2(GetPos().x, GetPos().y - 50.f));
		bomb->SetOwner(GetOwner());
		CreateObject(bomb, GROUP_TYPE::PROJ_PLAYER);

		DeleteObject(this);
		return;
	}

	mCurTime += DT / mArrivalTime;				// 베지어 곡선을 적용
	mRemainTime = 1 - mCurTime;

	Vect2 V0 = mvStartPoint * mRemainTime + mvCurvePoint * mCurTime;
	Vect2 V1 = mvCurvePoint * mRemainTime + mvTargetPoint * mCurTime;
	Vect2 V2 = V0 * mRemainTime + V1 * mCurTime;

	SetPos(V2);
	GetAnimator()->Update();
}

void Grenade_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
