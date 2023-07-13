#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"


<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
void CAnimation::SetAllFrameOffet(Vec2 _vOffset)
=======

void CAnimation::SetAllFrameOffet(Vect2 _vOffset)
>>>>>>> Stashed changes
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
	
<<<<<<< Updated upstream
	if ( mVecFrm[miCurFrm].fDuration < mfAccTime)
=======
	if (mVecFrm[miCurFrm].fDuration < mfAccTime)
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	}
}


void CAnimation::Render(HDC _dc)  
{
	if (mbFinish)
		return;

<<<<<<< Updated upstream
	CObject* pObj = mpAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += mVecFrm[miCurFrm].vOffset;	// Object Position 에 Offset 만큼 추가 이동위치

	// 렌더링 좌표로 변환
	vPos = CCamera::GetI()->GetRenderPos(vPos);

	Vec2 vScale = pObj->GetScale();

=======
	CObject* pObj = mpAnimator->GetObj();   
	Vect2 vPos = pObj->GetPos() + mVecFrm[miCurFrm].vOffset; // Add Animation Frame Offset

	// Convert LocalPos to RenderPos
	vPos = CCamera::GetI()->GetRenderPos(vPos);

	Vect2 vScale = pObj->GetScale();
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
		Vec2 pivot = pObj->GetPivot();  // 기준점 좌표 (pivot)
		float dx = pivot.x * cosAngle - pivot.y * sinAngle + vPos.x;
		float dy = pivot.x * sinAngle + pivot.y * cosAngle + vPos.y;

=======
		Vect2 pivot = pObj->GetPivot();  // 기준점 좌표 (pivot)
		float dx = pivot.x * cosAngle - pivot.y * sinAngle + vPos.x;
		float dy = pivot.x * sinAngle + pivot.y * cosAngle + vPos.y;

		// 회전 스케일 설정
>>>>>>> Stashed changes
		transform.eM11 = cosAngle;
		transform.eM12 = sinAngle;
		transform.eM21 = -sinAngle;
		transform.eM22 = cosAngle;
<<<<<<< Updated upstream
		transform.eDx = dx;
		transform.eDy = dy;
		
		// 변환 행렬 설정
		SetGraphicsMode(_dc, GM_ADVANCED);
		SetWorldTransform(_dc, &transform);

		// 이미지 출력
=======
		// 변환 좌표이동 설정
		transform.eDx = dx;
		transform.eDy = dy;
		
		// 그래픽 모드 설정 (GM_ADVANCED 고급 그래픽 모드)
		SetGraphicsMode(_dc, GM_ADVANCED);
		// 변환 행렬 설정
		SetWorldTransform(_dc, &transform);

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
		// 변환 행렬 초기화
		ModifyWorldTransform(_dc, nullptr, MWT_IDENTITY);
=======
		// 변환 행렬을 단위 행렬(Identity Matrix)로 초기화
		ModifyWorldTransform(_dc, nullptr, MWT_IDENTITY);
		// 변환 행렬 해제
>>>>>>> Stashed changes
		SetWorldTransform(_dc, nullptr);
	}
}


<<<<<<< Updated upstream
void CAnimation::CREATE(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize
	, Vec2 _vStep, float _fDuration, UINT _iFreamCount)
=======
void CAnimation::Create(CTexture* _pTex, Vect2 _vLT, Vect2 _vSliceSize
	, Vect2 _vStep, float _fDuration, UINT _iFreamCount)
>>>>>>> Stashed changes
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
