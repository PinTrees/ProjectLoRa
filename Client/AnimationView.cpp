#include "pch.h"
#include "AnimationView.h"

#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

AnimationView::AnimationView()
	:pCurAnimation(nullptr)
{
	CreateAnimator();
}

AnimationView::~AnimationView()
{

}


void AnimationView::Update()
{
	GetAnimator()->Update();

}

void AnimationView::Render(HDC _dc)
{
	Vect2 vPos = GetPos();
	CCamera::GetI()->GetRenderPos(vPos);

	Rectangle(_dc
		, vPos.x - GetScale().x / 2.f
		, vPos.y - GetScale().y / 2.f
		, vPos.x + GetScale().x / 2.f
		, vPos.y + GetScale().y / 2.f);

	CompnentRender(_dc);
}

