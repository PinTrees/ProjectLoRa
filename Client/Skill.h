#pragma once



enum class SKILL_USE_TYPE
{
	ACTIVE,
	PASSIVE,
};


class Skill
{
private:
	SKILL_TYPE mUID;

	SKILL_USE_TYPE mUseType;	// ��Ƽ�� ��ų���� �нú� ��ų���� ����
	bool	mIsActive;			// ���� ������� ����

	float	mCoolDelay;			// ��Ÿ��
	float	mCurDelay;

	int		mUseCount;			// ��밡�� Ƚ��

	int		mMaxSkillLv;		// �ִ� ����
	int		mCurSkillLv;		// ��ų ����


public:
	void SetMaxSkillLv(int _max) { mMaxSkillLv = _max; }

	SKILL_TYPE GetType() { return mUID; }
	bool IsActive() { return mIsActive; }

	void AddSkillLevel();


public:
	virtual bool IsStart() = 0;
	virtual void Start() {};
	virtual void ActiveUpdate() {};
	virtual void Update();

	bool IsCoolTimeOn();



public:
	Skill(SKILL_TYPE type, int _maxLv);
	virtual ~Skill();
};
