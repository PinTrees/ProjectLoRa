#pragma once


class CObject;
class CAnimation;
class CTexture;

<<<<<<< Updated upstream
class CAnimator
{
private:
	map<wstring, CAnimation*>	mMapAnim;
	CAnimation*					mpCurAnim;
	CObject*					mpOwner;
	bool						mbRepeat;
=======



class CAnimator
{
private:
	map<wstring, CAnimation*>	mMapAnim;		// Animation List
	CAnimation*					mpCurAnim;		// Current Animation
	CObject*					mpOwner;		// Owner Object
	bool						mbRepeat;		// Repeat or not
>>>>>>> Stashed changes


public:
	CObject* GetObj() { return mpOwner; }
	CAnimation* GetCurAnimation() { return mpCurAnim; }

<<<<<<< Updated upstream
public:
	void CreateAnimation(const wstring& _strName , CTexture* _pTex
		, Vec2 _vLT,Vec2 _vSliceSize,Vec2 _vStep, float _fDuration,UINT _iFreamCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void Update();
	void Render(HDC _dc);

=======

public:
	void CreateAnimation(const wstring& _strName , CTexture* _pTex, Vect2 _vLT,Vect2 _vSliceSize,Vect2 _vStep, float _fDuration,UINT _iFreamCount);
	CAnimation* FindAnimation(const wstring& _strName);

	void Play(const wstring& _strName, bool _bRepeat);


public:
	void Update();
	void Render(HDC _dc);


>>>>>>> Stashed changes
public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

