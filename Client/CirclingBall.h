#pragma once
#include "Skill.h"




class CirclingBall :
    public Skill
{
private:
    int     mPrevLv;                // 스킬의 이전 레벨
public:
    virtual void UseSkill();		// 스킬 사용
    virtual void CheckAvailable();	// 스킬 발동조건 체크

public:
    CirclingBall();
    virtual ~CirclingBall();

};

