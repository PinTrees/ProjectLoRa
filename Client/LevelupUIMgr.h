#pragma once

class LevelupUI;
class Player;

class LevelupUIMgr
{
	SINGLE(LevelupUIMgr);
private:
	LevelupUI*  mArrLvupUI[(UINT)LEVELUP_EFFECT::END];
	LevelupUI*	mCurLvupUI[3];

public:
	void Init();
	void Choice(Player* _player);
	void Delete();
};

