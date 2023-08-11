#pragma once



class SettingMgr
{
	SINGLE(SettingMgr);

private:
	FIND_PATH_TYPE	mFindPathType;
	BOOL			mbDamageText;
	int				mVolume;


public:
	void SetFindPathType(FIND_PATH_TYPE mType) { mFindPathType = mType; }
	FIND_PATH_TYPE GetFindPathType() { return mFindPathType;  }

	void SetDamageTextActive(BOOL active) { mbDamageText = active; }
	BOOL GetDamageTextActive() { return mbDamageText; }

	void SetVolume(int vol);
	int  GetVolume() { return mVolume; }


public:
	void Init();
};

