#include "pch.h"
#include "Box.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CTexture.h"

#include "CResMgr.h"
#include "CTimeMgr.h"




Box::Box()
	: mDeleteDelay(25.f)
	, mCurDelay(0.f)
	, mbOpened(false)
{
	SetScale(Vect2(128.f, 128.f) * 0.4f);

	CreateCollider();
	GetCollider()->SetScale(GetScale());

	CreateAnimator();
	
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Box_1", L"texture\\object\\box_1.bmp");
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2::zero, Vect2(128.f, 128.f), Vect2(128.f, 0.f), 1.f, 1);
	GetAnimator()->CreateAnimation(L"OPEN", pTex, Vect2(128.f, 0.f), Vect2(128.f, 128.f), Vect2(128.f, 0.f), 2.f, 1);

	GetAnimator()->Play(L"IDLE", true);
}

Box::~Box()
{
}




void Box::Update()
{
	GetAnimator()->Update();

	mCurDelay += DT;
	if (mCurDelay > mDeleteDelay)
	{
		DeleteObject(this);
		return;
	}

	if (mbOpened)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			DeleteObject(this);
		}
	}
}

void Box::Render(HDC _dc)
{
	CompnentRender(_dc);
}

void Box::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOgj = _pOther->GetObj();
	if (!mbOpened && pOgj->GetName() == L"Player")
	{
		mbOpened = true;
		GetAnimator()->Play(L"OPEN", false);
	}
}

