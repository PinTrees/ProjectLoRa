#include "pch.h"
#include "PlayerMgr.h"

SINGLE_HEADER(PlayerMgr);


PlayerMgr::PlayerMgr()
	: mpPlayer(nullptr)
{
}


PlayerMgr::~PlayerMgr()
{
	mpPlayer = nullptr;
}


void PlayerMgr::Init()
{
	mGold = 0;
}
