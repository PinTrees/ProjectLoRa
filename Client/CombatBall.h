#pragma once
#include "Skill.h"




class CombatBall :
    public Skill
{
private:
    int         mPrevLv;

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ


public:
    CombatBall();
    virtual ~CombatBall();
};

