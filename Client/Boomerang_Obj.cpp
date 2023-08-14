#include "pch.h"
#include "Boomerang_Obj.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CCore.h"



Boomerang_Obj::Boomerang_Obj()
	: mSpeed(600.f)
	, mAccel(700.f)
	, mCurTime()
	, mObjAngle()
	, mCollision(false)
{
	SetMaxDelay(4.f);
	SetDamageDelay(0.1f);
	SetName(L"Boomerang");
	CreateCollider();
	GetCollider()->SetScale(Vect2(80.f, 80.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Boomerang", L"texture\\effect\\4.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Boomerang", pTex, Vect2(336.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.5f, 1);
	SetScale(Vect2(100.f, 100.f));

	GetAnimator()->Play(L"Boomerang", true);
}

Boomerang_Obj::~Boomerang_Obj()
{
}


void Boomerang_Obj::Update()
{
	if (mCurTime > GetMaxDelay())
	{
		DeleteObject(this);
		return;
	}

	Vect2 vRes = CCore::GetI()->GetResolution();
	Vect2 vRenderPos = CCamera::GetI()->GetRenderPos(GetLocalPos());

	if (vRes.y < vRenderPos.y || 0 > vRenderPos.y)
	{
		mvDir = mvDir * Vect2(1.f, -1.f);
	}
	else if (vRes.x < vRenderPos.x || 0 > vRenderPos.x)
	{
		mvDir = mvDir * Vect2(-1.f, 1.f);
	}

	SetPos(GetPos() + mvDir * mSpeed * DT);
	SetAngle(mObjAngle);

	mCurTime += DT;
	mObjAngle += 1000 * DT;

	GetAnimator()->Update();
}

void Boomerang_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}

void Boomerang_Obj::OnCollisionEnter(CCollider* _pOther)
{
	mCollision = true;	// 진행중에 적과 만나면 진행방향을 바꾸기 위해 bool 값을 true로 변경
}
