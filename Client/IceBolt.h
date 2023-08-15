#pragma once
#include "Skill.h"




class IceBolt :
    public Skill
{
private:
    Vect2       mvDir;


public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

    virtual void AddSkillLevel();
public:
    IceBolt();
    virtual ~IceBolt();
};

