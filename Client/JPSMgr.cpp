#include "pch.h"
#include "JPSMgr.h"

#include "JPSCollision.h"
#include "JPSPath.h"
#include "JPSHeap.h"

#include "TileMapMgr.h"


SINGLE_HEADER(JPSMgr);


JPSMgr::JPSMgr()
{

}

JPSMgr::~JPSMgr()
{
	delete mJps;
	delete mCollisionData;
}



void JPSMgr::Init()
{
	mJps = new JPSPath;
	mCollisionData = new JPSCollision;

	mResultNodes.clear();
	mResultPos.clear();

	int width = TileMapMgr::GetI()->GetTileMapSizeX();
	int height = TileMapMgr::GetI()->GetTileMapSizeY();

	CreateTileMap(width, height);
}


void JPSMgr::CreateTileMap(Int32 height, Int32 width)
{
	mCollisionData->Create(width, height);
}



void JPSMgr::SetCollisionTile(Int32 x, Int32 y)
{
	mCollisionData->SetAt(x, y);
}


void JPSMgr::Find()
{
	mResultNodes.clear();

	// INIT
	mJps->Init(mCollisionData);

	// SEARCH
	mJps->Search(mStartPosX
		, mStartPosY
		, mTargetPosX
		, mTargetPosY
		, mResultNodes );

}

vector<Vect2>& JPSMgr::GetFinalPosList()
{
	mResultPos.clear();

	for (auto it = mResultNodes.begin(); it != mResultNodes.end(); ++it)
	{
		JPSCoord coord = *it;
		mResultPos.push_back(Vect2(coord.m_x, coord.m_y));
	}

	mResultNodes.clear();
	return mResultPos;
}


