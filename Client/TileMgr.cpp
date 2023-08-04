#include "pch.h"
#include "TileMgr.h"
#include "TileNode.h"


SINGLE_HEADER(TileMgr);

TileMgr::TileMgr()
	:mTileSizeX(0)
	, mTileSizeY(0)
{
}
TileMgr::~TileMgr()
{
	for (int i = 0; i < mNodes.size(); ++i)
	{
		for (int j = 0; j < mNodes[i].size(); ++j)
		{
			delete mNodes[i][j];
		}

	}
}

void TileMgr::CreateTileData(int x, int y)
{
	mTileSizeX = x;
	mTileSizeY = y;

	mNodes = vector<vector<TileNode*>> (x, vector<TileNode*>(y));

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j <y; ++j)
		{
			mNodes[i][j] = new TileNode(i, j);
		}
	}


}



void TileMgr::SetWallNode(int _x, int _y,bool _b)
{
	mNodes[_x][_y]->SetWall(_b);
}


