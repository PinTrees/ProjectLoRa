#pragma once


class CUI;



class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletUI;
	CUI*	mReroadUI;


public:
	void SetBulletUI(UINT count);


public:
	void Init();
};
