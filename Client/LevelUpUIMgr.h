#pragma once

struct tLevelUpEffectData
{
	wstring		titleStr;	// 타이틀
	wstring		infoStr;	// 세부설명
};


class LevelupUI;
class Player;


class LevelupUIMgr
{
	SINGLE(LevelupUIMgr)

private:
	map<LEVELUP_EFFECT, tLevelUpEffectData> mMapLvUpEffectData;
	array<LevelupUI*, 3>					mCurLvupUI;


public:
	void Init();
	void Choice();
	void Delete();
};
