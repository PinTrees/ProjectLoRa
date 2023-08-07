#pragma once



class Skill
{
private:
	SKILL_TYPE mType;

	wstring mIconStr;

	float   mSkillTime;			// ��ų ��Ÿ�� ��� �뵵
	float	mCooldown;			// ��Ÿ��

	int		mUseCount;			// ��밡�� Ƚ��
	int		mMaxSkillLv;		// �ִ� ����
	int		mCurSkillLv;		// ��ų ����

	bool	mAvailable;			// ��ų ��밡�� üũ ����

public:
	void SetCoolDown(float _cool) { mCooldown = _cool; }
	float GetCoolDown() { return mCooldown; }
	void SetMaxSkillLv(int _max) { mMaxSkillLv = _max; }

	void SetAvailable(bool _Ava) { mAvailable = _Ava; }
	bool GetAvilable() { return mAvailable; }

	int GetSkillLevel() { return mCurSkillLv; }
	SKILL_TYPE GetType() { return mType; }

	void SetSkillTime(float _time) { mSkillTime = _time; }
	float GetSkillTime() { return mSkillTime; }

	void SetIconStr(const wstring& str) { mIconStr = str; }
	wstring& GetIconStr() { return mIconStr; }

public:
	virtual void Update();

	virtual void UseSkill();		// ��ų ���
	virtual void CheckAvailable();	// ��ų �ߵ����� üũ

	void AddSkillLevel(); 


public: 
	Skill(SKILL_TYPE type, int _maxLv);
	~Skill();
};
