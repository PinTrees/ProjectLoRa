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

void CAnimation::SetAllFrameOffet(Vec2 _vOffset)
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

	Vec2 vScale = pObj->GetScale();


	if (pObj->GetAngle() <= 0.1f)
	{
		/*if (pObj->GetFlip())
		{
			FlipImage(_dc
				, (int)(vPos.x - vScale.x * 0.5f)
				, (int)(vPos.y - vScale.y * 0.5f)
				, (int)(vScale.x)
				, (int)(vScale.y)
				, mpTex->GetDC()
				, (int)(mVecFrm[miCurFrm].vLT.x)
				, (int)(mVecFrm[miCurFrm].vLT.y)
				, (int)(mVecFrm[miCurFrm].vSlice.x)
				, (int)(mVecFrm[miCurFrm].vSlice.y)
			);
		}
		else*/
		{
			TransparentBlt(_dc
				, (int)(vPos.x - vScale.x * 0.5f)
				, (int)(vPos.y - vScale.y * 0.5f)
				, (int)(vScale.x)
				, (int)(vScale.y)
				, mpTex->GetDC()
				, (int)(mVecFrm[miCurFrm].vLT.x)
				, (int)(mVecFrm[miCurFrm].vLT.y)
				, (int)(mVecFrm[miCurFrm].vSlice.x)
				, (int)(mVecFrm[miCurFrm].vSlice.y)
				, RGB(255, 0, 255)
			);
		}
	}
	else
	{
		// 이미지 회전을 위한 변환 행렬 생성
		XFORM transform;
		float angleRad = pObj->GetAngle() * PI / 180.0f;
		float cosAngle = cosf(angleRad);
		float sinAngle = sinf(angleRad);

		// 기준점 위치 계산
		Vec2 pivot = pObj->GetPivot();  // 기준점 좌표 (pivot)
		float dx = pivot.x * cosAngle - pivot.y * sinAngle + vPos.x;
		float dy = pivot.x * sinAngle + pivot.y * cosAngle + vPos.y;

		transform.eM11 = cosAngle;
		transform.eM12 = sinAngle;
		transform.eM21 = -sinAngle;
		transform.eM22 = cosAngle;
		transform.eDx = dx;
		transform.eDy = dy;
		/*transform.eM11 = cosf(pObj->GetAngle() * PI / 180.0f);
		transform.eM12 = sinf(pObj->GetAngle() * PI / 180.0f);
		transform.eM21 = -sinf(pObj->GetAngle() * PI / 180.0f);
		transform.eM22 = cosf(pObj->GetAngle() * PI / 180.0f);
		transform.eDx = vPos.x;
		transform.eDy = vPos.y;*/

		// 변환 행렬 설정
		SetGraphicsMode(_dc, GM_ADVANCED);
		SetWorldTransform(_dc, &transform);

		// 이미지 출력
		TransparentBlt(_dc
			, (int)(-vScale.x * 0.5f)
			, (int)(-vScale.y * 0.5f)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, mpTex->GetDC()
			, (int)(mVecFrm[miCurFrm].vLT.x)
			, (int)(mVecFrm[miCurFrm].vLT.y)
			, (int)(mVecFrm[miCurFrm].vSlice.x)
			, (int)(mVecFrm[miCurFrm].vSlice.y)
			, RGB(255, 0, 255)
		);

		// 변환 행렬 초기화
		ModifyWorldTransform(_dc, nullptr, MWT_IDENTITY);
		SetWorldTransform(_dc, nullptr);
	}
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
