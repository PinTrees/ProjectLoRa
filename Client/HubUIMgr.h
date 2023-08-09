#pragma once


class CUI;
class CRow;
class TextUI;
class Skill;


class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	CUI*		mBulletRowUI;
	CUI*		mReroadUI;
	TextUI*		mpLevelText;
	CRow*		mpSkillUI;

	TextUI*		mpGoldText;
	TextUI*		mpTimeext;


public:
	void SetBulletUI(UINT count);
	void SetLevelText(int level);
	void BuildSkillUI(vector<Skill*>& skills);
	void BuildGoldText();


public:
	void Init();
};

