#pragma once
class ToolMgr
{
	SINGLE(ToolMgr);
private:
	int		mCurTileIdx; // 현재 선택된 타일 인덱스

public:
	void SetTileIdx(int _idx) { mCurTileIdx = _idx; }
	

	int GetCurTileIdx() { return mCurTileIdx; }
};

