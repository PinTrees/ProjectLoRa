#pragma once
#include "Skill.h"




class CombatBall :
    public Skill
{
private:
    int         mPrevLv;

public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크


public:
    CombatBall();
    virtual ~CombatBall();
};

