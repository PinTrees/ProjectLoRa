#pragma once


class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	mMapAnim;
	CAnimation*					mpCurAnim;
	CObject*					mpOwner;
	bool						mbRepeat;


public:
	CObject* GetObj() { return mpOwner; }
	CAnimation* GetCurAnimation() { return mpCurAnim; }

public:
	void CreateAnimation(const wstring& _strName , CTexture* _pTex
		, Vec2 _vLT,Vec2 _vSliceSize,Vec2 _vStep, float _fDuration,UINT _iFreamCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void Update();
	void Render(HDC _dc);

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

