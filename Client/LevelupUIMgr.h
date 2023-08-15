#pragma once

struct tLvupEffectData
{
	wstring		infoStr;	// 세부설명
	wstring		titleStr;	// 타이틀
	wstring		iconStr;
};

enum class LEVELUP_TYPE
{
	STATE,
	SKILL,
	ITEM,
	END
};


struct tLeveUpEvent
{
	LEVELUP_TYPE	type;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;

	bool operator==(const tLeveUpEvent& other) const
	{
		return (type == other.type 
				&& lParam == other.lParam
				&& wParam == other.wParam);
	}
};



class CUI;
class LevelupUI;
class Player;


class LevelUpUIMgr
{
	SINGLE(LevelUpUIMgr)

private:
	map<STATEUP_TYPE, tLvupEffectData>	mMapLvupEffectData;
	map<SKILL_TYPE, tLvupEffectData>	mMapLvupEffectData_Skill;

	array<LevelupUI*, 3>					mCurLvupUI3;
	array<LevelupUI*, 2>					mCurLvupUI2;
	LevelupUI*								mCurLvupUI1;

	CUI*	mLevelUpUIPanel3;
	CUI*	mLevelUpUIPanel2;
	CUI*	mLevelUpUIPanel1;

public:
	void Init();
	void Choice();
	void Delete();
};
