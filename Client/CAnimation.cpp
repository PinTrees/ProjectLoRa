#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"


CAnimation::CAnimation()
	:mpAnimator(nullptr)
	, mpTex(nullptr)
	, miCurFrm(0)
	, mfAccTime(0.f)
	, mbFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (mbFinish)
		return;

	mfAccTime += fDT;
	
	if ( mVecFrm[miCurFrm].fDuration < mfAccTime)
	{
		++miCurFrm;

		if (mVecFrm.size() <= miCurFrm)
		{
			miCurFrm = -1;
			mbFinish = true;
			mfAccTime = 0.f;
			return;
		}
		mfAccTime = mfAccTime - mVecFrm[miCurFrm].fDuration;

	}
}

void CAnimation::Render(HDC _dc)  
{
	if (mbFinish)
		return;

	CObject* pObj = mpAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += mVecFrm[miCurFrm].vOffset;	// Object Position 에 Offset 만큼 추가 이동위치

	// 렌더링 좌표로 변환
	vPos = CCamera::GetI()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - mVecFrm[miCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y  - mVecFrm[miCurFrm].vSlice.y / 2.f)
		, (int)(mVecFrm[miCurFrm].vSlice.x)
		, (int)(mVecFrm[miCurFrm].vSlice.y)
		, mpTex->GetDC()
		, (int)(mVecFrm[miCurFrm].vLT.x)
		, (int)(mVecFrm[miCurFrm].vLT.y)
		, (int)(mVecFrm[miCurFrm].vSlice.x)
		, (int)(mVecFrm[miCurFrm].vSlice.y)
		, RGB(255, 0, 255)
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize
	, Vec2 _vStep, float _fDuration, UINT _iFreamCount)
{
	mpTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFreamCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep *(float) i;

		mVecFrm.push_back(frm);
	}
}
