#pragma once
#include "CObject.h"

class Particle :
	public CObject
{
private:
	wstring		mType;

	float		mDelay;
	float		mCurDelay;

public:
	void SetType(const wstring& _str) { mType = _str; }

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	CLONE(Particle);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);
public:
	Particle(const wstring& _type);
	~Particle();
};

