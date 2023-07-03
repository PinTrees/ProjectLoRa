#pragma once
#include "CObject.h"

class CTexture;
class Gun;

enum class PLAYER_STATE
{
	None,
	Idle,
	Attack,
	Run,
	Die,
	Dash,
};



class CPlayer :
	public CObject
{

private:
	float mfDelay;
	float mfCurDelay;

	Vec2 mvDashDir;

	Gun* mCurGun;

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

