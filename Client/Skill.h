#pragma once

typedef void(*Skill_Func)(void);
void TestSkill();

class Skill
{
private:

	bool	mIsActive;			// ��Ƽ�� ��ų���� �нú� ��ų���� ����
	float	mCooldown;			// ��Ÿ��
	int		mUseCount;			// ��밡�� Ƚ��
		
	int		mMaxSkillLv;		// �ִ� ����
	int		mCurSkillLv;		// ��ų ����

	Skill_Func mSkillFunc;		// ��ų�� �۵��ϴ� �Լ�(������)

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

