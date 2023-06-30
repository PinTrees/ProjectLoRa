#pragma once
#include "CObject.h"

class CTexture;


enum class PLAYER_STATE
{
	None,
	Idle,
	Attack,
	Run,
	Die,
};



class CPlayer :
	public CObject
{

private:
	float mfDelay;
	float mfCurDelay;

	PLAYER_STATE mState;

public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

private:
	void createMissile();

	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};

