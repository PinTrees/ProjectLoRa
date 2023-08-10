#pragma once
#include "Skill.h"

class CSound;


class Thunder :
    public Skill
{
private:
    CSound* mThunderSound;


public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크


public:
    Thunder();
    virtual ~Thunder();
};

