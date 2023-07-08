#pragma once
#include "CObject.h"

class CTexture;
class Gun;

enum class PLAYER_STATE
{
	NONE,
	Idle,
	ATTACK,
	Run,
	Die,
	Dash,
};



class Player :
	public CObject
{

private:
	float	mfDelay;
	float	mfCurDelay;

	Vec2	mvDashDir;

	Gun*	mCurGun;

	PLAYER_STATE mState;

public:
	virtual void Update()override;
	virtual void Render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _pOther);
private:

	void createMissile();

	void UpdateMove();
	void UpdateState();
	void UpdateAnimation();

	CLONE(Player);

public:
	Player();
	~Player();
};

