#pragma once


class CUI;



class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletUI;
	CUI*	mReroadUI;


public:
	void CreateBulletUI();
	void SetBulletUI();


public:
	void Init();
};

