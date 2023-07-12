#pragma once


class CObject;
class CAnimation;
class CTexture;




class CAnimator
{
private:
	map<wstring, CAnimation*>	mMapAnim;		// Animation List
	CAnimation*					mpCurAnim;		// Current Animation
	CObject*					mpOwner;		// Owner Object
	bool						mbRepeat;		// Repeat or not


public:
	CObject* GetObj() { return mpOwner; }
	CAnimation* GetCurAnimation() { return mpCurAnim; }


public:
	void CreateAnimation(const wstring& _strName , CTexture* _pTex, Vect2 _vLT,Vect2 _vSliceSize,Vect2 _vStep, float _fDuration,UINT _iFreamCount);
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	
	void Play(const wstring& _strName, bool _bRepeat);


public:
	void Update();
	void Render(HDC _dc);


public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

