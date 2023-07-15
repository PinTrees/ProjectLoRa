#include "pch.h"
#include "Box.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTexture.h"

#include "CResMgr.h"




Box::Box()
	: mDeleteDelay(25.f)
	, mCurDelay(0.f)
{
	SetScale(Vect2(128.f, 128.f) * 0.4f);
	CreateAnimator();
	
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Box_1", L"texture\\object\\box_1.bmp");
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2::zero, Vect2(128.f, 128.f), Vect2(128.f, 0.f), 1.f, 1);
	GetAnimator()->CreateAnimation(L"OPEN", pTex, Vect2(128.f, 0.f), Vect2(128.f, 128.f), Vect2(128.f, 0.f), 1.f, 1);

	GetAnimator()->Play(L"IDLE", true);
}

Box::~Box()
{
}




void Box::Update()
{
}

void Box::Render(HDC _dc)
{
	CompnentRender(_dc);
}

void Box::OnCollisionEnter(CCollider* _pOther)
{
}

