#pragma once
#include "Skill.h"


class CSound;


class Boomerang :
    public Skill
{
private:
    CSound* mpSound;


public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크


public:
    Boomerang();
    virtual ~Boomerang();
};

