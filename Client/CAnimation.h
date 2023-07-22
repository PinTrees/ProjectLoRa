#pragma once

// Frame Info
struct tAnimFrm
{
	Vect2	vLT;		// Left Top Pos
	Vect2	vSlice;		// Slice Size 
	Vect2	vOffset;	// Frame Offset
	float	fDuration;	// Frame Delay
};


class CAnimator;
class CTexture;
class CUI;



class CAnimation
{
private:
	wstring				mStrName;
	CAnimator*			mpAnimator;
	CTexture*			mpTexture;		 // Animation �ؽ���
	vector<tAnimFrm>	mVecFrm;	 // ��� ������ ����
	int					miCurFrm;	 // ���� ������
	float				mfAccTime;	 // ���� �ð�

	bool				mbFinish;	 // ��� �Ϸ� ����
	bool				mbPlay;		 // �������¿���

private:
	void SetName(const wstring& _strName) { mStrName = _strName; }

public:
	const wstring& GetName() { return mStrName; }

	UINT		GetMaxFrame() { return (UINT)mVecFrm.size(); }
	tAnimFrm&	GetFrame(int _iIdx) { return mVecFrm[_iIdx]; }
	int GetCurFrame() { return miCurFrm; }
	void SetFrame(int _iFrameIdx)
	{
		if (_iFrameIdx >= mVecFrm.size() || 0 > _iFrameIdx)
			return;

		mbFinish = false;
		miCurFrm = _iFrameIdx;
		mfAccTime = 0.f;
	}
	void SetAllFrameOffet(Vect2 _vOffset);

	void SetTex(CTexture* _texture) { mpTexture = _texture; }
	void SetPlay() { mbPlay = true; }
	void SetStop() { mbPlay = false; }
	bool IsFinish() { return mbFinish; } 
	bool IsPlay() { return mbPlay; }

public:
	void Update();
	void Render(HDC _dc);
	void RenderUI(CUI* ui, HDC dc);

	void Create(CTexture* _pTex, Vect2 _vLT, Vect2 _vSliceSize, Vect2 _vStep, float _fDuration, UINT _iFreamCount);


public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);


public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

