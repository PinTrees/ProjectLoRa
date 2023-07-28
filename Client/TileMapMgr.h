#pragma once





class TileMapMgr
{
	SINGLE(TileMapMgr);

private:
	UINT mTileMapSizeX;
	UINT mTileMapSizeY;


public:
	void SetTileMapSize(int x, int y) 
	{
		mTileMapSizeX = x;
		mTileMapSizeY = y;
	}

	UINT GetTileMapSizeX() { return mTileMapSizeX; }
	UINT GetTileMapSizeY() { return mTileMapSizeY; }


public:

};

