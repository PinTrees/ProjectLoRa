#pragma once
#include "Skill.h"


class Thunder :
    public Skill
{
private:

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    Thunder();
    ~Thunder();
};

