#pragma once
#include "Skill.h"

class SkillObj;

class EnergyBall :
    public Skill
{
private:
    Vect2           mvDir;          // ���������� �������

public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

    virtual void AddSkillLevel();
public:
    EnergyBall();
    virtual ~EnergyBall();
};

