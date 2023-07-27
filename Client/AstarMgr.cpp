#include "pch.h"
#include "AstarMgr.h"
#include "AstarNode.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
#include "PlayerMgr.h"
#include "Player.h"

SINGLE_HEADER(AstarMgr);


AstarMgr::AstarMgr()
	:mTileSizeX(0)
	, mTileSizeY(0)
	, mTargetX(0)
	, mTargetY(0)
	, mCurNode(nullptr)
	, mStartNode(nullptr)
	, mTargetNode(nullptr)
{
	mOpenNode.reserve(100);
	mCloseNode.reserve(100);
	mFinalNodes.reserve(100);
}

AstarMgr::~AstarMgr()
{
	for (int i = 0; i < mNodes.size(); ++i)
	{
		for (int j = 0; j < mNodes[i].size(); ++j)
		{
			delete mNodes[i][j];
		}

	}
}

void AstarMgr::SetWallNode(int _x, int _y)
{
	mNodes[_x][_y]->SetWall();
}

void AstarMgr::CreateTileData(int x, int y)
{
	mTileSizeX = x;
	mTileSizeY = y;

	mNodes = vector<vector< AstarNode*>>(x, vector< AstarNode*>(y));

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			mNodes[i][j] = new AstarNode(i, j);
		}
	}


}

vector<Vect2*> AstarMgr::AstarCall(int _x, int _y)
{
	vector<Vect2*> vResultPosList;

	if (mTileSizeX <= _x   || 0 > _x|| mTileSizeY <= _y|| 0 >  _y)
		return vResultPosList;

	Vect2 vPlayerPos = PlayerMgr::GetI()->GetPlayer()->GetPos();

	mTargetX = vPlayerPos.x / TILE_SIZE_RENDER;
	mTargetY = vPlayerPos.y / TILE_SIZE_RENDER;

	// ���۰� �� ���, ��������Ʈ�� ��������Ʈ, ����������Ʈ �ʱ�ȭ

	mStartNode = mNodes[_x][_y];
	mTargetNode = mNodes[mTargetX][mTargetY];

	mOpenNode.clear();
	mCloseNode.clear();
	mFinalNodes.clear();

	mOpenNode.push_back(mStartNode);
	while (mOpenNode.size() > 0)
	{
		int index = 0;
		mCurNode = mOpenNode[0];
		for (int i = 1; i < mOpenNode.size(); i++)
		{
			if (mOpenNode[i]->mF < mCurNode->mF && mOpenNode[i]->mH < mCurNode->mH)
			{
				index = i;
				mCurNode = mOpenNode[i];
			}
		}

		mOpenNode.erase(mOpenNode.begin() + index);
		mCloseNode.push_back(mCurNode);

		if (mCurNode == mTargetNode)
		{
			AstarNode* TargetCurnode = mTargetNode;
			while (TargetCurnode != mStartNode)
			{
				mFinalNodes.push_back(TargetCurnode);
				TargetCurnode = TargetCurnode->mParent;
			}
			mFinalNodes.push_back(mStartNode);

			break;
		}

		// �� , ������ , �Ʒ� , ����
		AddOpenNode(mCurNode->mX, mCurNode->mY - 1);
		AddOpenNode(mCurNode->mX + 1, mCurNode->mY);
		AddOpenNode(mCurNode->mX, mCurNode->mY + 1);
		AddOpenNode(mCurNode->mX - 1, mCurNode->mY);

		AddOpenNode(mCurNode->mX - 1, mCurNode->mY - 1);
		AddOpenNode(mCurNode->mX + 1, mCurNode->mY - 1);
		AddOpenNode(mCurNode->mX + 1, mCurNode->mY + 1);
		AddOpenNode(mCurNode->mX - 1, mCurNode->mY + 1);


	}

	std::reverse(mFinalNodes.begin(), mFinalNodes.end());
	for (int i = 0; i < mFinalNodes.size(); i++)
	{
		vResultPosList.push_back(new Vect2(mFinalNodes[i]->mX * TILE_SIZE_RENDER + TILE_SIZE
			, mFinalNodes[i]->mY * TILE_SIZE_RENDER + TILE_SIZE));
	}

	return vResultPosList;
}



void AstarMgr::AddOpenNode(int checkX, int checkY)
{
	// �����¿� ������ ����� �ʰ�, ���� �ƴϸ鼭, ��������Ʈ�� ���ٸ�
	if (checkX >= 0 && checkX < mTileSizeX && checkY >= 0
		&& checkY < mTileSizeY && !mNodes[checkX][checkY]->IsWall())
	{
		for (int i = 0; i < mCloseNode.size(); ++i)
		{
			if (mCloseNode[i] == mNodes[checkX][checkY])
			{
				return;
			}
		}

		//// �밢�� ����, �� ���̷� ��� �ȵ�
		//if (allowDiagonal) if (NodeArray[CurNode.x - bottomLeft.x, checkY - bottomLeft.y].isWall && NodeArray[checkX - bottomLeft.x, CurNode.y - bottomLeft.y].isWall) return;

		//// �ڳʸ� �������� ���� ������, �̵� �߿� �������� ��ֹ��� ������ �ȵ�
		//if (dontCrossCorner) if (NodeArray[CurNode.x - bottomLeft.x, checkY - bottomLeft.y].isWall || NodeArray[checkX - bottomLeft.x, CurNode.y - bottomLeft.y].isWall) return;


		// �̿���忡 �ְ�, ������ 10, �밢���� 14���
		AstarNode* NeighborNode = mNodes[checkX][checkY];
		int MoveCost = mCurNode->mG + 10;

		bool flage = false;
		for (int i = 0; i < mOpenNode.size(); ++i)
		{
			if (mOpenNode[i] == NeighborNode)
			{
				flage = true;
				break;
			}
		}

		// �̵������ �̿����G���� �۰ų� �Ǵ� ��������Ʈ�� �̿���尡 ���ٸ� G, H, ParentNode�� ���� �� ��������Ʈ�� �߰�
		if (MoveCost < NeighborNode->mG || !flage)
		{
			NeighborNode->mG = MoveCost;
			NeighborNode->mH = (abs(NeighborNode->mX - mTargetNode->mX) + abs(NeighborNode->mY - mTargetNode->mY)) * 10;
			NeighborNode->mParent = mCurNode;

			mOpenNode.push_back(NeighborNode);
		}
	}
}




