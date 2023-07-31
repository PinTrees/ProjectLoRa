#pragma once


class Skill;

class DatabaseMgr
{
	SINGLE(DatabaseMgr);

private:
	Skill* mArrSkill[(UINT)SKILL_TYPE::END];


public:
	Skill* GetSkill(SKILL_TYPE type);


public:
	void Init();
};

