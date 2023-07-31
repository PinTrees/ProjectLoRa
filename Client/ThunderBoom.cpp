#include "pch.h"
#include "ThunderBoom.h"

#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"


ThunderBoom::ThunderBoom()
{
	SetName(L"Thunder_Bomb");

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Thunder_Bomb", L"texture\\effect\\103.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Boom", pTex, Vect2(0.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.04f, 9);
	SetScale(Vect2(48.f, 64.f) * 3.0f);
	GetAnimator()->FindAnimation(L"Boom")->SetAllFrameOffet(Vect2(0.f, GetScale().y * -0.5f));

	GetAnimator()->Play(L"Boom", false);
}

ThunderBoom::~ThunderBoom()
{
}

void ThunderBoom::Update()
{
	GetAnimator()->Update();

	if (GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(this);
		return;
	}
}

void ThunderBoom::Render(HDC _dc)
{
	SkillObj::Render(_dc);
}
