#pragma once

struct tLevelUpEffectData
{
	wstring		titleStr;	// Ÿ��Ʋ
	wstring		infoStr;	// ���μ���
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
