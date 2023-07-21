#pragma once
#include "CObject.h"

class CAnimation;
class CTexture;

class AnimationView :
	public CObject
{
public:
	CAnimation* pCurAnimation;
public:
	void SetAnimation(CAnimation* _anim) { pCurAnimation = _anim; }

	CAnimation* GetAnimation() { return pCurAnimation; }

public:
	virtual void Update();		// Object Game Logic
	virtual void Render(HDC _dc);	// Scene Rendering

private:
	CLONE(AnimationView);
public:
	AnimationView();
	virtual ~AnimationView();
};

