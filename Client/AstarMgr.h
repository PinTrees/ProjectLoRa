#pragma once


// Astat 노드
struct tAstarNode
{
	int x;
	int y;

	int h;
	int g;

	bool isWall = false;

	tAstarNode* parent;

	int GetF() { return h + g; }

	tAstarNode(bool wall, int _x, int _y)
		: isWall(wall)
		, x(_x)
		, y (_y)
		, parent(nullptr)
		, h(0)
		, g(0)
	{ 
	}
};


class AstarMgr
{
	SINGLE(AstarMgr);

private:
	int mTileX;
	int mTileY;

	// 타일 정보 노드
	vector<vector<tAstarNode*>>	mMapNode;

	vector<tAstarNode*> mVecOpenNode;
	vector<tAstarNode*> mVecCloseNode;

	vector<tAstarNode*> mFinalNodeList;
	vector<Vect2>		mFinalPosList;

	tAstarNode* mStartNode;			// 시작 노드
	tAstarNode* mTargetNode;		// 도착 노드
	tAstarNode* mCurNode;			// 현재 탐색 노드

	int mTargetX;
	int mTargetY;

public:
	void CreatTileMap(int x, int y);
	void OpenListAdd(int x, int y);

	void SetObstacleTile(int x, int y) { mMapNode[x][y]->isWall = true; }

	void SetTargetPos(int x, int y) 
	{
		x = x < 0 ? 0 : x;
		y = y < 0 ? 0 : y;

		mTargetX = x;
		mTargetY = y;

		mTargetNode = mMapNode[x][y];
	}
	void SetStartPos(int x, int y) 
	{ 
		x = x < 0 ? 0 : x;
		y = y < 0 ? 0 : y;

		x = x >= mTileX ? mTileX - 1 : x;
		y = y >= mTileY ? mTileY - 1 : y;

		mStartNode = mMapNode[x][y];
	}

	void Find();

	vector<Vect2>& GetFinalPosList()
	{
		mFinalPosList.clear();

		for (int i = 0; i < mFinalNodeList.size(); ++i)
		{
			mFinalPosList.push_back(Vect2(mFinalNodeList[i]->x, mFinalNodeList[i]->y));
		}

		return mFinalPosList;
	}
};

