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
	: mType(_type)
{

	CreateCollider();
<<<<<<< Updated upstream
	GetCollider()->SetOffsetPos(GetPivot() - Vec2(0.f, 15.f));
	GetCollider()->SetScale(Vec2(40.f, 35.f));
=======
	GetCollider()->SetOffsetPos(GetPivot() - Vect2(0.f, 15.f));
	GetCollider()->SetScale(Vect2(40.f, 35.f));
>>>>>>> Stashed changes


	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"ENV_" + mType, L"texture\\map\\" + mType + L".bmp");

	CreateAnimator();

	if (mType == L"1")
	{
<<<<<<< Updated upstream
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(64.f, 96.f), Vec2(64.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
		SetScale(Vec2(64.f, 96.f));
	}
	else if (mType == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
		SetScale(Vec2(32.f, 32.f));
	}
	else if (mType == L"101")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 0.1f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, -20.f));
		SetScale(Vec2(80.f, 80.f) * 2.f);
		
		SetPivot(Vec2(0.f, 0.f));
		GetCollider()->SetOffsetPos(GetPivot() - Vec2(0.f, 25.f));
=======
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(64.f, 96.f), Vect2(64.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
		SetScale(Vect2(64.f, 96.f));
	}
	else if (mType == L"2")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(32.f, 32.f), Vect2(32.f, 0.f), 0.1f, 4);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
		SetScale(Vect2(32.f, 32.f));
	}
	else if (mType == L"101")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 0.1f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, -20.f));
		SetScale(Vect2(80.f, 80.f) * 2.f);
		
		SetPivot(Vect2(0.f, 0.f));
		GetCollider()->SetOffsetPos(GetPivot() - Vect2(0.f, 25.f));
>>>>>>> Stashed changes
		GetCollider()->SetScale(GetScale() * 0.7f);
	}


	else if (mType == L"back_1")
	{
<<<<<<< Updated upstream
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 5.f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vec2(0.f, 0.f));

		SetPivot(Vec2(0.f, 0.f));
	}



=======
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vect2(0.f, 0.f), Vect2(80.f, 80.f), Vect2(80.f, 0.f), 5.f, 1);
		GetAnimator()->FindAnimation(L"IDLE")->SetAllFrameOffet(Vect2(0.f, 0.f));

		SetPivot(Vect2(0.f, 0.f));
	}


>>>>>>> Stashed changes
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