#pragma once

#include "Monster.h"

class Boss :
    public Monster
{
public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;

public:
	Boss(const wstring& uid);
	~Boss();

};

