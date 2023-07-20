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

	SKILL_USE_TYPE mUseType;	// 액티브 스킬인지 패시브 스킬인지 구분
	bool	mIsActive;			// 현재 사용중인 상태

	float	mCoolDelay;			// 쿨타임
	float	mCurDelay;

	int		mUseCount;			// 사용가능 횟수

	int		mMaxSkillLv;		// 최대 레벨
	int		mCurSkillLv;		// 스킬 레벨


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
