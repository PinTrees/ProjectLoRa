#pragma once


class Skill;


// ���� �����ͺ��̽� �޴����� ����
// ���� �� �����ϴ� ��� ������ ���� ���� ����
// Item, Skill, Bullet, Monster
class SkillMgr
{
	SINGLE(SkillMgr);

private:
	Skill* mArrSkill[(UINT)SKILL_TYPE::END];


public:
	Skill* GetSkill(SKILL_TYPE type);


public:
	void Init();
};

