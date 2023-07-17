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
	GetCollider()->SetScale(Vect2(15, 15));

	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"Effect" + _type, L"texture\\effect\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(70.f, 52.f), Vect2(70.f, 0.f), 0.05f, 6);
		SetScale(Vect2(70.f, 52.f) * 1.5f);
	}
	else if (_type == L"4")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.05f, 11);
		SetScale(Vect2(48.f, 48.f) * 1.5f);
	}
	else if (_type == L"5")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.05f, 9);
		SetScale(Vect2(48.f, 48.f) * 1.5f);
	}

	// 101 ~ 105 Àü·ù ÀÌÆåÆ®
	else if (_type == L"101")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(64.f, 64.f), Vect2(64.f, 0.f), 0.05f, 9);
		SetScale(Vect2(64.f, 64.f) * 1.f);
	}
	else if (_type == L"102")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 128.f), Vect2(48.f, 0.f), 0.05f, 15);
		SetScale(Vect2(48.f, 128.f) * 1.5f);
	}
	else if (_type == L"103")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 64.f), Vect2(48.f, 0.f), 0.05f, 10);
		SetScale(Vect2(48.f, 64.f) * 3.f);
	}
	else if (_type == L"104")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(64.f, 64.f), Vect2(64.f, 0.f), 0.03f, 14);
		SetScale(Vect2(64.f, 64.f) * 3.f);
	}
	else if (_type == L"105")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(48.f, 48.f), Vect2(48.f, 0.f), 0.05f, 16);
		SetScale(Vect2(48.f, 48.f) * 3.f);
	}

	else if (_type == L"201")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(96.f, 96.f), Vect2(96.f, 0.f), 0.05f, 8);
		SetScale(Vect2(96.f, 96.f) * 3.f);
	}
	else if (_type == L"202")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(96.f, 96.f), Vect2(96.f, 0.f), 0.05f, 8);
		SetScale(Vect2(96.f, 96.f) * 2.f);
	}
	GetAnimator()->Play(L"IDLE", false);
}




Particle::~Particle()
{

}

void Particle::Update()
{
	mCurDelay += DT;

	GetAnimator()->Update();

	if (GetAnimator()->GetCurAnimation()->IsFinish())
	{
		DeleteObject(this);
		return;
	}
}

void Particle::Render(HDC _dc)
{
	Vect2 vPos = GetPos();
	Vect2 vScale = GetScale();

	CompnentRender(_dc);
}

void Particle::OnCollisionEnter(CCollider* _pOther)
{
}