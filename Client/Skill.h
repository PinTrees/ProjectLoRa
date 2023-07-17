#pragma once

typedef void(*Skill_Func)(void);
void TestSkill();

class Skill
{
private:

	bool	mIsActive;			// 액티브 스킬인지 패시브 스킬인지 구분
	float	mCooldown;			// 쿨타임
	int		mUseCount;			// 사용가능 횟수
		
	int		mMaxSkillLv;		// 최대 레벨
	int		mCurSkillLv;		// 스킬 레벨

	Skill_Func mSkillFunc;		// 스킬이 작동하는 함수(포인터)

public:
	void SetSkillFunc(Skill_Func _skill) { mSkillFunc = _skill; }
	void SetMaxSkillLv(int _max) { mMaxSkillLv = _max; }

public:
	void UseSkill();
	void AddSkillLevel();

public:
	Skill(Skill_Func _skill, int _maxLv);
	~Skill();
};

