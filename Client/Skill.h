#pragma once

struct tSkillInfo
{
	float	Cooldown;			// 쿨타임
	int		UseCount;			// 사용가능 횟수
	int		MaxSkillLv;			// 최대 레벨
	int		CurSkillLv;			// 스킬 레벨
};

class Skill
{
private:
	SKILL_TYPE	mType;

	wstring		mIconStr;

	tSkillInfo	mtSkillInfo;

	float		mSkillTime;			// 스킬 쿨타임 재는 용도
	float		mCooldown;			// 쿨타임

	int			mUseCount;			// 사용가능 횟수
	int			mMaxSkillLv;		// 최대 레벨
	int			mCurSkillLv;		// 스킬 레벨

	bool	mAvailable;			// 스킬 사용가능 체크 변수

public:
	tSkillInfo GetSkillInfo() { return mtSkillInfo; }

	void	SetCoolDown(float _cool) { mCooldown = _cool; }
	float	GetCoolDown() { return mCooldown; }
	
	void	SetMaxSkillLv(int _max) { mMaxSkillLv = _max; }
	int		GetMaxSkillLv() { return mMaxSkillLv; }

	void	SetAvailable(bool _Ava) { mAvailable = _Ava; }
	bool	GetAvilable() { return mAvailable; }

	int		GetSkillLevel() { return mCurSkillLv; }
	SKILL_TYPE GetType() { return mType; }

	void	SetSkillTime(float _time) { mSkillTime = _time; }
	float	GetSkillTime() { return mSkillTime; }

	void	SetIconStr(const wstring& str) { mIconStr = str; }
	const wstring& GetIconStr() { return mIconStr; }


public:
	virtual void Update();

	virtual void UseSkill();		// 스킬 사용
	virtual void CheckAvailable();	// 스킬 발동조건 체크

	virtual void AddSkillLevel(); 


public: 
	Skill(SKILL_TYPE type, int _maxLv);
	virtual ~Skill();
};
