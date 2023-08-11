#pragma once
#include "Skill.h"


class CSound;


class Boomerang :
    public Skill
{
private:
    CSound* mpSound;


public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ


public:
    Boomerang();
    virtual ~Boomerang();
};

