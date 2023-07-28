#include "pch.h"
#include "AstarMgr.h"


SINGLE_HEADER(AstarMgr);

AstarMgr::AstarMgr()
{

}

AstarMgr::~AstarMgr()
{
    for (int i = 0; i < mTileX; i++)
    {
        for (int j = 0; j < mTileY; j++)
        {
            delete mMapNode[i][j];
        }
    }

    mMapNode.clear();
}



void AstarMgr::CreatTileMap(int x, int y)
{
    mTileX = x;
    mTileY = y;

    mMapNode = vector<vector<tAstarNode*>>(mTileX, vector<tAstarNode*>(mTileY));

    for (int i = 0; i < mTileX; i++)
    {
        for (int j = 0; j < mTileY; j++)
        {
            mMapNode[i][j] = new tAstarNode(false, i, j);
        }
    }
}



void AstarMgr::Find()
{
    mVecOpenNode.clear();
    mVecCloseNode.clear();
    mFinalNodeList.clear();

    mVecOpenNode.push_back(mStartNode);

    if (mTargetNode->isWall)
        return;

    if (mTargetX < 1 || mTargetY < 1 || mTileX - 1 <= mTargetX || mTileY - 1 <= mTargetY)
        return;

    if (mTileX <= mTargetX || 0 > mTargetX || mTileY <= mTargetY || 0 > mTargetY)
        return;

    if (mMapNode[mTargetX + 1][mTargetY]->isWall
        && mMapNode[mTargetX][mTargetY + 1]->isWall
        && mMapNode[mTargetX - 1][mTargetY]->isWall
        && mMapNode[mTargetX][mTargetY - 1]->isWall)
        return;

    bool isFind = false;

    while (mVecOpenNode.size() > 0)
    {
        int curNodeIdx = 0;
        mCurNode = mVecOpenNode[0];

        for (int i = 1; i < mVecOpenNode.size(); i++)
        {
            if (mVecOpenNode[i]->GetF() <= mCurNode->GetF() && mVecOpenNode[i]->h < mCurNode->h)
            {
                curNodeIdx = i;
                mCurNode = mVecOpenNode[i];
            }
        }
        
        mVecCloseNode.push_back(mCurNode);
        mVecOpenNode.erase(mVecOpenNode.begin() + curNodeIdx);

        if (mCurNode == mTargetNode)
        {
            tAstarNode* pTargetCurNode = mTargetNode;
            while (pTargetCurNode != mStartNode)
            {
                mFinalNodeList.push_back(pTargetCurNode);
                pTargetCurNode = pTargetCurNode->parent;
            }
            mFinalNodeList.push_back(mStartNode);
            reverse(mFinalNodeList.begin(), mFinalNodeList.end());

            isFind = true;
            break;
        }

        OpenListAdd(mCurNode->x,     mCurNode->y + 1);
        OpenListAdd(mCurNode->x + 1, mCurNode->y);
        OpenListAdd(mCurNode->x,     mCurNode->y - 1);
        OpenListAdd(mCurNode->x - 1, mCurNode->y);

        OpenListAdd(mCurNode->x - 1, mCurNode->y - 1);
        OpenListAdd(mCurNode->x + 1, mCurNode->y - 1);
        OpenListAdd(mCurNode->x - 1, mCurNode->y + 1);
        OpenListAdd(mCurNode->x + 1, mCurNode->y + 1);
    }

    if (isFind)
    {
    }
}




void AstarMgr::OpenListAdd(int checkX, int checkY)
{
    if (checkX >= 0 && checkX < mTileX && checkY >= 0 && checkY < mTileY &&
        !mMapNode[checkX][checkY]->isWall)
    {
        for (int i = 0; i < mVecCloseNode.size(); ++i)
        {
            if (mVecCloseNode[i] == mMapNode[checkX][checkY])
            {
                return;
            }
        }

        if (mMapNode[mCurNode->x][checkY]->isWall && mMapNode[checkX][mCurNode->y]->isWall) return;
        if (mMapNode[mCurNode->x][checkY]->isWall || mMapNode[checkX][mCurNode->y]->isWall) return;

        tAstarNode* pNeighborNode = mMapNode[checkX][checkY];
        int moveCost = mCurNode->g + (mCurNode->x - checkX == 0 || mCurNode->y - checkY == 0 ? 10 : 14);
        bool isOpenList = false;

        for (int i = 0; i < mVecOpenNode.size(); ++i)
        {
            if (mVecOpenNode[i] == pNeighborNode)
            {
                isOpenList = true;
                break;
            }
        }

        if (moveCost < pNeighborNode->g || !isOpenList)
        {
            pNeighborNode->g = moveCost;
            pNeighborNode->h = (abs(pNeighborNode->x - mTargetNode->x) + abs(pNeighborNode->y - mTargetNode->y)) * 10;
            pNeighborNode->parent = mCurNode;

            mVecOpenNode.push_back(pNeighborNode);
        }
    }
}
