#pragma once
#include "Monster.h"



enum class BOSS_STATE 
{
	TRACE,
	ATK,
	DIE,
	END
};


class CImageUI;
class CColumn;
class CSound;


class Boss :
	public Monster
{
private:
	CImageUI*	mpHpBar;
	CColumn*	mpHpUI;

public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;
	virtual void OnCollisionEnter(CCollider* _pOther) override;

	CLONE(Boss);


public:
	Boss(const wstring& uid);
	virtual ~Boss() override;
};

