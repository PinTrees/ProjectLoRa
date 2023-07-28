#include "pch.h"
#include "Environment.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CCollider.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"



Environment::Environment(const wstring& _type)
	: mUID(_type)
{
	CreateCollider();
	CreateAnimator();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"ENV_" + mUID, L"texture\\map\\" + mUID + L".bmp");

	if (mUID == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(64.f, 96.f), Vect2(64.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
	}
	else if (mUID == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(32.f, 32.f), Vect2(32.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
	}
	else if (mUID == L"101")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.1f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
	}

	else if (mUID == L"back_1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 5.f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));
	}

	GetAnimator()->Play(L"IDLE", true);
}

Environment::~Environment()
{
}



void Environment::Update()
{
	GetAnimator()->Update();
}

void Environment::Render(HDC _dc)
{
	CompnentRender(_dc);
}