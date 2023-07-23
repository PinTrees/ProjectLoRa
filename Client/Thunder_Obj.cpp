#include "pch.h"
#include "Thunder_Obj.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CCollider.h"

Thunder_Obj::Thunder_Obj()
	: mCurDelay()
{
	SetMaxDelay(0.5f);		// 스킬 지속시간 세팅
	SetDamageDelay(0.9f);	// ~초마다 데미지를 입힘

	SetName(L"Thunder");
	SetScale(Vect2(200.f, 200.f));

	CreateCollider();
	GetCollider()->SetScale(Vect2(100.f, 100.f));
	GetCollider()->SetOffsetPos(Vect2(0.f, 50.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Thunder", L"texture\\effect\\103.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Thunder", pTex, Vect2(0.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.1f, 9);

	GetAnimator()->Play(L"Thunder", false);
}

Thunder_Obj::~Thunder_Obj()
{
}

void Thunder_Obj::Update()
{
	mCurDelay += DT;

	if (mCurDelay >= GetMaxDelay())		// 스킬 지속시간이 지나면 오브젝트를 삭제
	{
		DeleteObject(this);
		mCurDelay = 0.f;
		return;
	}

	GetAnimator()->Update();
}

void Thunder_Obj::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
