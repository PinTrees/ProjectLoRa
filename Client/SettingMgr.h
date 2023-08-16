#pragma once



class SettingMgr
{
	SINGLE(SettingMgr);

private:
	FIND_PATH_TYPE	mFindPathType;
	BOOL			mbDamageText;
	BOOL			mbMonsterHpbarActive;
	int				mVolume;
	int				mBgmVolume;


public:
	void SetFindPathType(FIND_PATH_TYPE mType) { mFindPathType = mType; }
	FIND_PATH_TYPE GetFindPathType() { return mFindPathType;  }

	void SetDamageTextActive(BOOL active) { mbDamageText = active; }
	BOOL GetDamageTextActive() { return mbDamageText; }

	void SetMonsterHpbarActive(BOOL active) { mbMonsterHpbarActive = active; }
	BOOL GetMonsterHpbarActive() { return mbMonsterHpbarActive; }

	void SetVolume(int vol);
	int  GetVolume() { return mVolume; }

	void SetBGMVolume(int vol);
	int  GetBGMVolume() { return mBgmVolume; }

public:
	void Init();
};

