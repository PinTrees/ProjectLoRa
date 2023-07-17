#pragma once
class ToolMgr
{
	SINGLE(ToolMgr);
private:
	int		mCurTileIdx;

public:
	void SetTileIdx(int _idx) { mCurTileIdx = _idx; }
	

	int GetTileIdx() { return mCurTileIdx; }
};

