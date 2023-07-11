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


void CAnimation::SetAllFrameOffet(Vect2 _vOffset)
{
	for (int i = 0; i < mVecFrm.size(); i++)
	{
		mVecFrm[i].vOffset = _vOffset;
	}
}


void CAnimation::Update()
{
	if (mbFinish)
		return;

	mfAccTime += DT;
	
	if (mVecFrm[miCurFrm].fDuration < mfAccTime)
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
	Vect2 vPos = pObj->GetPos() + mVecFrm[miCurFrm].vOffset; // Add Animation Frame Offset

	// Convert LocalPos to RenderPos
	vPos = CCamera::GetI()->GetRenderPos(vPos);

	Vect2 vScale = pObj->GetScale();

	if (pObj->GetAngle() <= 0.1f)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = pObj->GetAlpha();

		AlphaBlend(_dc
			, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, mpTex->GetDC()
			, (int)(mVecFrm[miCurFrm].vLT.x)
			, (int)(mVecFrm[miCurFrm].vLT.y)
			, (int)(mVecFrm[miCurFrm].vSlice.x)
			, (int)(mVecFrm[miCurFrm].vSlice.y)
			, bf);
	}
	else
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = pObj->GetAlpha();

		// 이미지 회전을 위한 변환 행렬 생성
		XFORM transform;
		float angleRad = pObj->GetAngle() * PI / 180.0f;
		float cosAngle = cosf(angleRad);
		float sinAngle = sinf(angleRad);

		// 기준점 위치 계산
		Vect2 pivot = pObj->GetPivot();  // 기준점 좌표 (pivot)
		float dx = pivot.x * cosAngle - pivot.y * sinAngle + vPos.x;
		float dy = pivot.x * sinAngle + pivot.y * cosAngle + vPos.y;

		// 회전 스케일 설정
		transform.eM11 = cosAngle;
		transform.eM12 = sinAngle;
		transform.eM21 = -sinAngle;
		transform.eM22 = cosAngle;
		// 변환 좌표이동 설정
		transform.eDx = dx;
		transform.eDy = dy;
		
		// 그래픽 모드 설정 (GM_ADVANCED 고급 그래픽 모드)
		SetGraphicsMode(_dc, GM_ADVANCED);
		// 변환 행렬 설정
		SetWorldTransform(_dc, &transform);

		AlphaBlend(_dc
			, (int)(-vScale.x * 0.5f)
			, (int)(-vScale.y * 0.5f)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, mpTex->GetDC()
			, (int)(mVecFrm[miCurFrm].vLT.x)
			, (int)(mVecFrm[miCurFrm].vLT.y)
			, (int)(mVecFrm[miCurFrm].vSlice.x)
			, (int)(mVecFrm[miCurFrm].vSlice.y)
			, bf);

		// 변환 행렬을 단위 행렬(Identity Matrix)로 초기화
		ModifyWorldTransform(_dc, nullptr, MWT_IDENTITY);
		// 변환 행렬 해제
		SetWorldTransform(_dc, nullptr);
	}
}


void CAnimation::Create(CTexture* _pTex, Vect2 _vLT, Vect2 _vSliceSize
	, Vect2 _vStep, float _fDuration, UINT _iFreamCount)
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
