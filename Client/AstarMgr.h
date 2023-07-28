#pragma once

class AstarNode;

class AstarMgr
{
	SINGLE(AstarMgr);
private:
	int mTileSizeX;
	int mTileSizeY;

	int mTargetX;
	int mTargetY;

	vector<vector<AstarNode*>> mNodes;

	vector<AstarNode*>	mOpenNode;
	vector<AstarNode*>	mCloseNode;
	vector<AstarNode*>	mFinalNodes;

	AstarNode* mCurNode;
	AstarNode* mStartNode;
	AstarNode* mTargetNode;

	vector<Vect2>		mvResultPosList;

public:
	void SetWallNode(int _x, int _y);
public:
	void CreateTileData(int x, int y);
	vector<Vect2>& AstarCall(int _x, int _y);

private:
	void AddOpenNode(int x, int y);
};

