#pragma once
#include "Skill.h"




class CrossDagger :
    public Skill
{
private:
    int         mCount;             // 표창 개수

public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크

public:
    CrossDagger();
    ~CrossDagger();
};

