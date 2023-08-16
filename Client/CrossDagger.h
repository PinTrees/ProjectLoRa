#pragma once
#include "Skill.h"


class CSound;

class CrossDagger :
    public Skill
{
private:
    CSound*     mpSound;
    int         mCount;             // 표창 개수

public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크


public:
    CrossDagger();
    virtual ~CrossDagger();
};

