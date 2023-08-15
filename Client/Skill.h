#pragma once

struct tSkillInfo
{
	float	Cooldown;			// ��Ÿ��
	int		UseCount;			// ��밡�� Ƚ��
	int		MaxSkillLv;			// �ִ� ����
	int		CurSkillLv;			// ��ų ����
};

class Skill
{
private:
	SKILL_TYPE	mType;

	wstring		mIconStr;

	tSkillInfo	mtSkillInfo;

	float		mSkillTime;			// ��ų ��Ÿ�� ��� �뵵
	float		mCooldown;			// ��Ÿ��

	int			mUseCount;			// ��밡�� Ƚ��
	int			mMaxSkillLv;		// �ִ� ����
	int			mCurSkillLv;		// ��ų ����

	bool	mAvailable;			// ��ų ��밡�� üũ ����

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

	virtual void UseSkill();		// ��ų ���
	virtual void CheckAvailable();	// ��ų �ߵ����� üũ

	virtual void AddSkillLevel(); 


public: 
	Skill(SKILL_TYPE type, int _maxLv);
	virtual ~Skill();
};
