#pragma once


class CUI;
class CRow;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletRowUI;
	CUI*	mReroadUI;

	// 사용되지 않음. 설정 창 접근 UI
	CUI*	mSettingBtn;
	CUI*	mSettingUI;


public:
	void SetBulletUI(UINT count);


public:
	void Init();
};

