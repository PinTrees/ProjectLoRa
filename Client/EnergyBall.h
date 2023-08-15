#pragma once
#include "Skill.h"

class SkillObj;

class EnergyBall :
    public Skill
{
private:
    Vect2           mvDir;          // 에너지볼의 진행방향

public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크

    virtual void AddSkillLevel();
public:
    EnergyBall();
    virtual ~EnergyBall();
};

