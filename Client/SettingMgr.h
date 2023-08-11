#pragma once



class SettingMgr
{
	SINGLE(SettingMgr);

private:
	FIND_PATH_TYPE mFindPathType;
	BOOL	mbDamageText;


public:
	void SetFindPathType(FIND_PATH_TYPE mType) { mFindPathType = mType; }
	FIND_PATH_TYPE GetFindPathType() { return mFindPathType;  }

	void SetDamageTextActive(BOOL active) { mbDamageText = active; }
	BOOL GetDamageTextActive() { return mbDamageText; }


public:
	void Init();
};

