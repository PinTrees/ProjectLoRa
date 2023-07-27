#pragma once

class AstarNode
{
private:
	int mG; // ���ݱ��� �̵��� �Ÿ�
	int mH;	// ������ ���� ���� �Ÿ�
	int mF;	// ���� ��

	int mX;	
	int mY;

	AstarNode* mParent; // �θ���
	bool		isWall; // ���� ��� ��ġ�� ������ �ƴ���


public:
	int GetF() { return mG + mH; } // ����ġ��
	int GetG() { return mG; } // ����ġ��
	int GetH() { return mH; } // ����ġ��

	void SetF(int _var) { mF = _var; } 
	void SetG(int _var) { mG = _var; } 
	void SetH(int _var) { mH = _var; } 

	void SetWall() { isWall = true; }
	bool IsWall() { return isWall; }


public:
	friend class AstarMgr;

	AstarNode();
	AstarNode(int x, int y);
	AstarNode(const AstarNode& other);
	~AstarNode();
};

