#pragma once

#include "Player.h"

class Player;




class PlayerMgr
{
	SINGLE(PlayerMgr)

private:
	Player*		mpPlayer;


public:
	void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	Vect2 GetTileIndex() { mpPlayer->GetPos() / TILE_SIZE_RENDER; }
	Player* GetPlayer() { return mpPlayer; }
};

