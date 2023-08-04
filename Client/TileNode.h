#pragma once

class Environment;

class TileNode
{
private:
	int mG; // 지금까지 이동한 거리
	int mH;	// 앞으로 남은 예상 거리
	int mF;	// 더한 값

	int mX; //타일인덱스
	int mY;

	TileNode* mParent; // 부모노드
	bool		isWall; // 현재 노드 위치가 벽인지 아닌지

public:
	int GetF() { return mG + mH; } // 가중치값
	int GetG() { return mG; } // 가중치값
	int GetH() { return mH; } // 가중치값

	void SetF(int _var) { mF = _var; }
	void SetG(int _var) { mG = _var; }
	void SetH(int _var) { mH = _var; }

	void SetWall(bool _b) { isWall = _b; }
	bool IsWall() { return isWall; }

public:
	friend class AstarMgr;

	TileNode();
	TileNode(int x, int y);
	TileNode(const TileNode& other);
	~TileNode();
};

