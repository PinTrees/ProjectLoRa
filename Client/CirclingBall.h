#pragma once
#include "Skill.h"




class CirclingBall :
    public Skill
{
private:
    int     mPrevLv;                // ��ų�� ���� ����
public:
    virtual void UseSkill();		// ��ų ���
    virtual void CheckAvailable();	// ��ų �ߵ����� üũ

public:
    CirclingBall();
    virtual ~CirclingBall();

};

