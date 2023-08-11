#pragma once

class Player;




class PlayerMgr
{
	SINGLE(PlayerMgr)

private:
	Player*		mpPlayer;
	UINT		mGold;


public:
	void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	Player* GetPlayer() { return mpPlayer; }

	void AddGold(UINT amount) { mGold += amount; }
	UINT GetGold() { return mGold; }


public:
	void Init();
};

