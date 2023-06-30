#pragma once
#include "global.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;
};

class CAnimation
{
private:
	wstring				mStrName;
	CAnimator*			mpAnimator;
	CTexture*			mpTex;		// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm>	mVecFrm;	// 모든 프레임 정보
	int					miCurFrm;	// 현재 프레임
	float				mfAccTime;	// 시간누적

	bool				mbFinish;	// 재생 끝에 도달 여부
public:
	const wstring& GetName() { return mStrName; }
	bool IsFinish() { return mbFinish; }
	void SetFrame(int _iFrameIdx)
	{
		mbFinish = false;
		miCurFrm = _iFrameIdx;
		mfAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return mVecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)mVecFrm.size(); }
	
private:
	void SetName(const wstring& _strName) { mStrName = _strName; }


public:
	void Update();
	void Render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFreamCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

