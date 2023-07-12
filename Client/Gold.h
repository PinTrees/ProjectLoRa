#pragma once

#include "CObject.h"

class CCollider;

class Gold
	: public CObject
{
private:
	float mDeleteDelay;
	float mCurDelay;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Gold);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;


public:
	Gold();
	~Gold();
};

