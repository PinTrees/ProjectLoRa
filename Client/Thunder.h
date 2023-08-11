#pragma once
#include "Skill.h"

class CSound;


class Thunder :
    public Skill
{
private:
    CSound* mThunderSound;


public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ


public:
    Thunder();
    virtual ~Thunder();
};

