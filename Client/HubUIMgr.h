#pragma once


class CUI;
class CRow;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletRowUI;
	CUI*	mReroadUI;

	CUI*	mSettingBtn;
	CUI*	mSettingUI;


public:
	void SetBulletUI(UINT count);


public:
	void Init();
};

