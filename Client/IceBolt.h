#pragma once
#include "Skill.h"




class IceBolt :
    public Skill
{
private:

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    IceBolt();
    ~IceBolt();
};

