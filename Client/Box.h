#pragma once


#include "CObject.h"

class CCollider;

class Box
	: public CObject
{
private:
	float mDeleteDelay;
	float mCurDelay;

	bool mbOpened;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Box);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;


public:
	Box();
	virtual ~Box() override;
};

