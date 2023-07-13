#include "pch.h"
#include "CCamera.h"


#include "CObject.h"
#include "CCore.h"	

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CTexture.h"


CCamera::CCamera()
	:mpTargetObj(nullptr)
	, mfTime(1.f)
	, mfSpeed(0.f)
	, mfAccTime(0.f)
	, mEffectTex(nullptr)
{
}

CCamera::~CCamera()
{
}


void CCamera::Init()
{
<<<<<<< Updated upstream
    Vec2 vRes =	CCore::GetI()->GetResolution();
=======
    Vect2 vRes =	CCore::GetI()->GetResolution();
>>>>>>> Stashed changes
	mEffectTex = CResMgr::GetI()->CreateTexture(L"CamEffectTex", (UINT)vRes.x, (UINT)vRes.y);
}


void CCamera::Update()
{
	if (nullptr != mpTargetObj)
	{
		if (mpTargetObj->IsDead())
		{
			mpTargetObj = nullptr;
		}
		else
		{
			mvLookAt = mpTargetObj->GetPos();
		}
	}

	
	if (KEY_HOLD(KEY::UP))
		mvLookAt.y -= DT * 500.f;
	if (KEY_HOLD(KEY::DOWN))
		mvLookAt.y += DT * 500.f;
	if (KEY_HOLD(KEY::LEFT))
		mvLookAt.x -= DT * 500.f;
	if (KEY_HOLD(KEY::RIGHT))
		mvLookAt.x += DT * 500.f;


	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	calDiff();
}


void CCamera::Render(HDC dc)
{
	if (mEffects.empty())
		return;

	tCamEffect& effect = mEffects.front();
	effect.time += DT;

	float amount = (float)(effect.time / effect.duration);

	if (amount > 1.f) amount = 1.f;
	if (amount < 0.f) amount = 0.f;

	int alpha = 0;	

	if (CAM_EFFECT::FADE_OUT == effect.effect)
	{
		alpha = (int)(255.f * amount);
	}
	else if (CAM_EFFECT::FADE_IN == effect.effect)
	{
		alpha = (int)(255.f * (1.f - amount));
	}


	// =============
<<<<<<< Updated upstream
	// Effect Render
=======
	// tEffectLv Render
>>>>>>> Stashed changes
	// =============
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(dc
		, 0, 0
		, mEffectTex->Width()
		, mEffectTex->Heigth()
		, mEffectTex->GetDC()
		, 0, 0
		, mEffectTex->Width()
		, mEffectTex->Heigth()
		, bf);


<<<<<<< Updated upstream
	// Effect Delete
=======
	// tEffectLv Delete
>>>>>>> Stashed changes
	if (effect.duration < effect.time)
	{
		mEffects.pop_front();
	}
}


void CCamera::calDiff()
{
	// 이전 LookAt 과 현재 look 의 차이값을 보정해서 현재의 LookAt을 구한다.
	
	mfAccTime += DT;

	if (mfTime <= mfAccTime )
	{
		mvCurLookAt = mvLookAt;
	}
	else
	{
<<<<<<< Updated upstream
		Vec2 vLookDir = mvLookAt - mvPrevLookAt;
=======
		Vect2 vLookDir = mvLookAt - mvPrevLookAt;
>>>>>>> Stashed changes
		mvCurLookAt = mvPrevLookAt + vLookDir.Normalize() * mfSpeed * DT;
	}


	//Lerp(mvPrevLookAt, mvLookAt,)



<<<<<<< Updated upstream
	Vec2 vResolution = CCore::GetI()->GetResolution();
	Vec2 vCenter = vResolution / 2;
=======
	Vect2 vResolution = CCore::GetI()->GetResolution();
	Vect2 vCenter = vResolution / 2;
>>>>>>> Stashed changes

	mvDiff = mvCurLookAt - vCenter;
	mvPrevLookAt = mvCurLookAt;
}