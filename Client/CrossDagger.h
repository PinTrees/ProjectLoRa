#pragma once
#include "Skill.h"




class CrossDagger :
    public Skill
{
private:
    int         mCount;             // ǥâ ����

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    CrossDagger();
    ~CrossDagger();
};

