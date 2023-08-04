#pragma once

class TileNode;

class AstarMgr
{
	SINGLE(AstarMgr);
private:
	int mTileSizeX;
	int mTileSizeY;

	int mTargetX;
	int mTargetY;

	vector<vector<TileNode*>>* mNodes;

	vector<TileNode*>	mOpenNode;
	vector<TileNode*>	mCloseNode;
	vector<TileNode*>	mFinalNodes;

	TileNode* mCurNode;
	TileNode* mStartNode;
	TileNode* mTargetNode;

	vector<Vect2>		mvResultPosList;

public:
	void init();
public:
	vector<Vect2>& AstarCall(int _x, int _y);

private:
	void AddOpenNode(int x, int y);
};

