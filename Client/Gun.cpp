#include "pch.h"
#include "Gun.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "Particle.h"

#include "CPlayer.h"

Gun::Gun(const wstring& _type)
	: m_tTheta(PI / 4.f)
	, mDelay(1.f)
	, mCurDelay(0.f)
	, mOwner(nullptr)
{
	CTexture* pTex = CResMgr::GetI()->LoadTexture(L"GUN" + _type, L"texture\\gun\\" + _type + L".bmp");
	CreateAnimator();

	if (_type == L"1")
	{
		GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(28.f, 16.f), Vec2(28.f, 0.f), 5.f, 1);
		SetScale(Vec2(28.f, 16.f) * 1.5f);
		SetPivot(Vec2(-30.f, 0.f));
		SetAngleOffset(180);
	}


	GetAnimator()->Play(L"IDLE", true);
}




Gun::~Gun()
{

}

void Gun::Update()
{
	GetAnimator()->Update();

	if (mOwner == nullptr)
	{
		return;
	}

	SetPos(mOwner->GetLocalPos() + Vec2(0.f, -45.f));
}

void Gun::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	CompnentRender(_dc);
}
