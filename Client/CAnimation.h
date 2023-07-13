#pragma once

<<<<<<< Updated upstream
struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;
=======
// Frame Info
struct tAnimFrm
{
	Vect2	vLT;		// Left Top Pos
	Vect2	vSlice;		// Slice Size 
	Vect2	vOffset;	// Frame Offset
	float	fDuration;	// Frame Delay
>>>>>>> Stashed changes
};


class CAnimator;
class CTexture;




class CAnimation
{
private:
	wstring				mStrName;
	CAnimator*			mpAnimator;
<<<<<<< Updated upstream
	CTexture*			mpTex;		// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm>	mVecFrm;	// 모든 프레임 정보
	int					miCurFrm;	// 현재 프레임
	float				mfAccTime;	// 시간누적

	bool				mbFinish;	// 재생 끝에 도달 여부
public:
	const wstring& GetName() { return mStrName; }
	bool IsFinish() { return mbFinish; }
=======
	CTexture*			mpTex;		 // Animation 텍스쳐
	vector<tAnimFrm>	mVecFrm;	 // 모든 프레임 정보
	int					miCurFrm;	 // 현재 프레임
	float				mfAccTime;	 // 누적 시간

	bool				mbFinish;	 // 재생 완료 여부


private:
	void SetName(const wstring& _strName) { mStrName = _strName; }

public:
	const wstring& GetName() { return mStrName; }

	UINT		GetMaxFrame() { return (UINT)mVecFrm.size(); }
	tAnimFrm&	GetFrame(int _iIdx) { return mVecFrm[_iIdx]; }
	
>>>>>>> Stashed changes
	void SetFrame(int _iFrameIdx)
	{
		mbFinish = false;
		miCurFrm = _iFrameIdx;
		mfAccTime = 0.f;
	}
<<<<<<< Updated upstream

	void SetAllFrameOffet(Vec2 _vOffset);
	

	tAnimFrm& GetFrame(int _iIdx) { return mVecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)mVecFrm.size(); }
	

private:
	void SetName(const wstring& _strName) { mStrName = _strName; }
=======
	void SetAllFrameOffet(Vect2 _vOffset);
	
	bool IsFinish() { return mbFinish; } 
>>>>>>> Stashed changes


public:
	void Update();
	void Render(HDC _dc);

<<<<<<< Updated upstream
	void CREATE(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFreamCount);
=======
	void Create(CTexture* _pTex, Vect2 _vLT, Vect2 _vSliceSize, Vect2 _vStep, float _fDuration, UINT _iFreamCount);
>>>>>>> Stashed changes


public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

