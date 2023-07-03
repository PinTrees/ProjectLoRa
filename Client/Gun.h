#pragma once

#include "CObject.h"

class CPlayer;

class Gun :
	public CObject
{
private:
	float     m_tTheta; // 이동 방향
	wstring		mType;

	CPlayer*	mOwner;

	float		mDelay;
	float		mCurDelay;


public:
	void SetType(const wstring& _str) { mType = _str; }
	void SetOwner(CPlayer* _owner) { mOwner = _owner; }


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Gun);


public:
	Gun(const wstring& _type);
	~Gun();
};

