#pragma once
#include "Skill.h"


class CSound;

class CrossDagger :
    public Skill
{
private:
    CSound*     mpSound;
    int         mCount;             // ǥâ ����

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ


public:
    CrossDagger();
    virtual ~CrossDagger();
};

