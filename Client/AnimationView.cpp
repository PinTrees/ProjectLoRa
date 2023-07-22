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
	CObject::Render(_dc);
}

