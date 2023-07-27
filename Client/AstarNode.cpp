#include "pch.h"
#include "AstarNode.h"

AstarNode::AstarNode()
	: mF(0)
	, mG(0)
	, mH(0)
	, mParent(nullptr)
	, isWall(false)
{

}

AstarNode::AstarNode(int x, int y)
	: mF(0)
	, mG(0)
	, mH(0)
	, mX(x)
	, mY(y) 
	, mParent(nullptr)
	, isWall(false)
{


}

AstarNode::AstarNode(const AstarNode& other)
	: mF(other.mF)
	, mG(other.mG)
	, mH(other.mH)
	, mX(other.mX)
	, mY(other.mY)
	, mParent(other.mParent)
	, isWall(other.isWall)
{
}


AstarNode::~AstarNode()
{

}
