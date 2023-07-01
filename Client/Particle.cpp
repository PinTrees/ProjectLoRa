#include "pch.h"
#include "Particle.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"


Particle::Particle(const wstring& _type)
	: mType(_type)
	, mDelay(1.5f)
	, mCurDelay(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(15, 15));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\effect\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(70.f, 52.f), Vec2(70.f, 0.f), 0.05f, 6);
		SetScale(Vec2(70.f, 52.f) * 1.5f);
	}
	else if (_type == L"4")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.03f, 11);
		SetScale(Vec2(48.f, 48.f) * 1.5f);
	}
	else if (_type == L"5")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 0.03f, 9);
		SetScale(Vec2(48.f, 48.f) * 1.5f);
	}

	GetAnimator()->Play(L"IDLE", false);
}




Particle::~Particle()
{

}

void Particle::Update()
{
	mCurDelay += fDT;

	GetAnimator()->Update();

	if (GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(this);
		return;
	}
}

void Particle::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	CompnentRender(_dc);
}

void Particle::OnCollisionEnter(CCollider* _pOther)
{
}