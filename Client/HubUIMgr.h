#pragma once


class CUI;
class CRow;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CRow*	mBulletRowUI;
	CUI*	mReroadUI;


public:
	void SetBulletUI(UINT count);


public:
	void Init();
};

