#pragma once

struct tLevelUpEffectData
{
	wstring		titleStr;	// Ÿ��Ʋ
	wstring		infoStr;	// ���μ���
};


class LevelupUI;
class CUI;
class Player;


class LevelupUIMgr
{
	SINGLE(LevelupUIMgr)

private:
	map<LEVELUP_EFFECT, tLevelUpEffectData> mMapLvUpEffectData;
	array<LevelupUI*, 3>					mCurLvupUI;
	CUI*	mLevelUpUIPanel;

public:
	void Init();
	void Choice();
	void Delete();
};
