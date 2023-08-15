#pragma once


class Skill;

class DatabaseMgr
{
	SINGLE(DatabaseMgr);

private:
	Skill* mArrSkill[(UINT)SKILL_TYPE::END];


public:
	Skill* GetSkill(SKILL_TYPE type);
	Skill** GetSkillList() { return mArrSkill; }


public:
	void Init();
};

