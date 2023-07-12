#include "pch.h"
#include "CAnimation.h"

// Manager Header
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"




CAnimation::CAnimation()
	:mpAnimator(nullptr)
	, mpTexture(nullptr)
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
			, mpTexture->GetDC()
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
			, mpTexture->GetDC()
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
	mpTexture = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFreamCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep *(float) i;

		mVecFrm.push_back(frm);
	}
}



void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	// Animation 의 이름을 저장한다. (데이터 직렬화)	
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(mStrName.begin(), mStrName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// Animation이 사용하는 텍스쳐
	fprintf(pFile, "[Texture Name]\n");
	strName = string(mpTexture->GetKey().begin(), mpTexture->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(mpTexture->GetRelativePath().begin(), mpTexture->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// 프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)mVecFrm.size());

	for (size_t i = 0; i < mVecFrm.size(); i++)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", i);


		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)mVecFrm[i].vLT.x, (int)mVecFrm[i].vLT.y);


		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)mVecFrm[i].vSlice.x, (int)mVecFrm[i].vSlice.y);


		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)mVecFrm[i].vOffset.x, (int)mVecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", mVecFrm[i].fDuration);


		fprintf(pFile, "\n\n");

	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetI()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// Animation 의 이름을 읽어온다.
	string str;
	char szBuff[255] = {};
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	mStrName = wstring(str.begin(), str.end());

	// 참조하는 텍스쳐 이름 및 경로
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	mpTexture = CResMgr::GetI()->LoadTexture(strTexKey, strTexPath);


	//// 프레임 개수
	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	//모든 프레임 정보
	tAnimFrm frm = {};
	for (int i = 0; i < iFrameCount; i++)
	{
		POINT pt = {};
		while (true)
		{
			FScanf(szBuff, pFile);

			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vSlice = pt;

			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break;
			}
		}
		mVecFrm.push_back(frm);
	}

	fclose(pFile);
}
