#pragma once


class CUI;
class CRow;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*	mBulletRowUI;
	CUI*	mReroadUI;

	// ������ ����. ���� â ���� UI
	CUI*	mSettingBtn;
	CUI*	mSettingUI;


public:
	void SetBulletUI(UINT count);


public:
	void Init();
};

