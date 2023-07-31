#pragma once


class CSystemMgr
{
	SINGLE(CSystemMgr);

private:
	BOOL	mbDebug;


public:
	void SetDebug(BOOL active) { mbDebug = active; }
	BOOL GetDebug() { return mbDebug; } 
};

