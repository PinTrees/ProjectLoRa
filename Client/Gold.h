#pragma once

#include "CObject.h"

class CCollider;
class CSound;

class Gold
	: public CObject
{
private:
	float mDeleteDelay;
	float mCurDelay;

	float	mGatherDelay;
	float	mCurGatherDelay;
	bool	mbGather;
	CSound* mpCoinSound;


public:
	void SetGather() 
	{ 
		if (mbGather)
			return;

		mbGather = true;
		mGatherDelay = 0.7f;
	};


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Gold);


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;


public:
	Gold();
	virtual ~Gold() override;
};

