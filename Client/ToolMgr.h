#pragma once
class ToolMgr
{
	SINGLE(ToolMgr);
private:
	int		mCurTileIdx; // ���� ���õ� Ÿ�� �ε���

public:
	void SetTileIdx(int _idx) { mCurTileIdx = _idx; }
	

	int GetCurTileIdx() { return mCurTileIdx; }
};

