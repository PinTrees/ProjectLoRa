#pragma once
#include "Skill.h"




class Boomerang :
    public Skill
{
private:

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    Boomerang();
    ~Boomerang();
};

