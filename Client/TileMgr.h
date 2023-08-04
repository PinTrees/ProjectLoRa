#pragma once

class TileNode;


class TileMgr
{
	SINGLE(TileMgr);

private:
	vector<vector<TileNode*>> mNodes;
	int mTileSizeX;
	int mTileSizeY;

public:
	vector<vector<TileNode*>>* GetTileNode() { return &mNodes; }

public:
	void CreateTileData(int x, int y);
	void SetWallNode(int _x, int _y,bool _b);
	void SetEven(int _x, int _y,CObject* _even);
	Vect2 GetTileSize() { return Vect2(mTileSizeX, mTileSizeY); };

};

