#pragma once

class Environment;

class TileNode
{
private:
	int mG; // ���ݱ��� �̵��� �Ÿ�
	int mH;	// ������ ���� ���� �Ÿ�
	int mF;	// ���� ��

	int mX; //Ÿ���ε���
	int mY;

	TileNode* mParent; // �θ���
	bool		isWall; // ���� ��� ��ġ�� ������ �ƴ���

public:
	int GetF() { return mG + mH; } // ����ġ��
	int GetG() { return mG; } // ����ġ��
	int GetH() { return mH; } // ����ġ��

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

