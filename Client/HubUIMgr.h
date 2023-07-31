#pragma once


class CUI;
class CRow;
class TextUI;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletRowUI;
	CUI*	mReroadUI;
	TextUI* mpLevelText;


public:
	void SetBulletUI(UINT count);
	void SetLevelText(int level);


public:
	void Init();
};

