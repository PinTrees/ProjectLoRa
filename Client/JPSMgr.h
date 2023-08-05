#pragma once

class JPSCollision;
class JPSPath;
class JPSCoord;


class JPSMgr
{
	SINGLE(JPSMgr);

private:
	JPSCollision*		mCollisionData;
	JPSPath*			mJps;

	vector<Vect2>	mResultPos;

	Int32 mStartPosX;
	Int32 mStartPosY;

	Int32 mTargetPosX;
	Int32 mTargetPosY;

	list<JPSCoord> mResultNodes; // Result for JPS


public:
	void Init();


public:
	void CreateTileMap(Int32 x, Int32 y);
	void SetCollisionTile(Int32 x, Int32 y);

	void SetStartPos(Int32 x, Int32 y) { mStartPosX = x; mStartPosY = y; }
	void SetTargetPos(Int32 x, Int32 y) { mTargetPosX = x; mTargetPosY = y; }

	void Find();
	vector<Vect2>& GetFinalPosList();
};

