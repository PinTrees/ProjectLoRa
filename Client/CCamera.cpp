#include "pch.h"
#include "CCamera.h"


#include "CObject.h"
#include "CCore.h"	

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	:mpTargetObj(nullptr)
	, mfTime(1.f)
	, mfSpeed(0.f)
	,mfAccTime(0.5f)
{
}

CCamera::~CCamera()
{
}


void CCamera::Update()
{
	if (mpTargetObj)
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
		mvLookAt.y -= fDT * 500.f;
	if (KEY_HOLD(KEY::DOWN))
		mvLookAt.y += fDT * 500.f;
	if (KEY_HOLD(KEY::LEFT))
		mvLookAt.x -= fDT * 500.f;
	if (KEY_HOLD(KEY::RIGHT))
		mvLookAt.x += fDT * 500.f;


	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	calDiff();
}

void CCamera::calDiff()
{
	// 이전 LookAt 과 현재 look 의 차이값을 보정해서 현재의 LookAt을 구한다.
	
	mfAccTime += fDT;

	if (mfTime <= mfAccTime )
	{
		mvCurLookAt = mvLookAt;
	}
	else
	{
		Vec2 vLookDir = mvLookAt - mvPrevLookAt;
		mvCurLookAt = mvPrevLookAt + vLookDir.Normalize() * mfSpeed * fDT;
	}


	//Lerp(mvPrevLookAt, mvLookAt,)



	Vec2 vResolution = CCore::GetI()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	mvDiff = mvCurLookAt - vCenter;
	mvPrevLookAt = mvCurLookAt;
}