#pragma once



class SettingMgr
{
	SINGLE(SettingMgr);

private:
	FIND_PATH_TYPE mFindPathType;


public:
	void SetFindPathType(FIND_PATH_TYPE mType) { mFindPathType = mType; }
	FIND_PATH_TYPE GetFindPathType() { return mFindPathType;  }


public:
	void Init();
};

