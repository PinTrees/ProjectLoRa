#pragma once
#include "Skill.h"




class Grenade :
    public Skill
{
private:

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

    virtual void AddSkillLevel();
public:
    Grenade();
    virtual ~Grenade();
};

