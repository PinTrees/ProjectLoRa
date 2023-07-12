#pragma once
#include "CCompnent.h"

class CObject;
class CAnimation;
class CTexture;




class CAnimator
	: public CCompnent
{
private:
	map<wstring, CAnimation*>	mMapAnim;		// Animation List
	CAnimation*					mpCurAnim;		// Current Animation
	bool						mbRepeat;		// Repeat or not


public:
	CObject* GetObj() { return GetO(); }
	CAnimation* GetCurAnimation() { return mpCurAnim; }


public:
	void CreateAnimation(const wstring& _strName , CTexture* _pTex, Vect2 _vLT,Vect2 _vSliceSize,Vect2 _vStep, float _fDuration,UINT _iFreamCount);
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC _dc) override;


public:
	CAnimator();
	virtual ~CAnimator() override;

	friend class CObject;
};

