#pragma once

class Player;




class PlayerMgr
{
	SINGLE(PlayerMgr)

private:
	Player*		mpPlayer;


public:
	void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	Player* GetPlayer() { return mpPlayer; }
};

