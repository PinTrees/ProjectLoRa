#include "pch.h"
#include "TileNode.h"

#include "Environment.h"


TileNode::TileNode()
	: mF(0)
	, mG(0)
	, mH(0)
	, mParent(nullptr)
	, isWall(false)
{

}

TileNode::TileNode(int x, int y)
	: mF(0)
	, mG(0)
	, mH(0)
	, mX(x)
	, mY(y) 
	, mParent(nullptr)
	, isWall(false)
{


}

TileNode::TileNode(const TileNode& other)
	: mF(other.mF)
	, mG(other.mG)
	, mH(other.mH)
	, mX(other.mX)
	, mY(other.mY)
	, mParent(other.mParent)
	, isWall(other.isWall)
{
}


TileNode::~TileNode()
{

}
