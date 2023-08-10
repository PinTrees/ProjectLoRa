#include "pch.h"
#include "Monster_Arrow.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "PlayerMgr.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "Player.h"
#include "Monster.h"

Monster_Arrow::Monster_Arrow()
	: mCurTime()
	, mbDestroy(false)
{
	SetName(L"Monster_Arrow");
	CreateCollider();
	GetCollider()->SetScale(Vect2(25.f, 25.f) * 0.5f);
	GetCollider()->SetOffsetPos(Vect2(0.f, 0.f));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Monster_Arrow", L"texture\\effect\\5.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Monster_Arrow", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.5f, 1);
	SetScale(Vect2(30.f, 30.f) * 3.f);

	GetAnimator()->Play(L"Monster_Arrow", true);
}

Monster_Arrow::~Monster_Arrow()
{
}


void Monster_Arrow::Update()
{
	if (mCurTime > 3.f)					// 일정시간이 지나면 오브젝트가 사라짐
	{
		DeleteObject(this);
		mCurTime = 0.f;
		mbDestroy = true;
		return;
	}

	Vect2 vPos = GetPos();

	vPos += mvDir * DT * 100.f;

	SetPos(vPos);
	GetAnimator()->Update();

	mCurTime += DT;
}

void Monster_Arrow::Render(HDC _dc)
{
	CompnentRender(_dc);
}

void Monster_Arrow::OnCollisionEnter(CCollider* _pOther)
{
	if (mbDestroy) return;

	CObject* pObject = _pOther->GetObj();

	if (pObject->GetName() == L"Player")
	{
		Player* pPlayer = PlayerMgr::GetI()->GetPlayer();
		Monster* pMonster = (Monster*)GetOwner();

		pPlayer->AddDamage(pMonster->GetInfo().atk);
		DeleteObject(this);
	}
}
