#pragma once
#include "Skill.h"




class IceBolt :
    public Skill
{
private:

public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크

public:
    IceBolt();
    ~IceBolt();
};

