#pragma once
#include "Skill.h"
class HolyArea :
    public Skill
{
private:
    int     mPrevLv;

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    HolyArea();
    ~HolyArea();
};

