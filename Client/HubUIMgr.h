#pragma once


class CUI;
class CRow;
class TextUI;
class Skill;

 
class HubUIMgr
{
	SINGLE(HubUIMgr)

private:
	TextUI*		mpLevelText;
	CRow*		mpSkillUI;

	TextUI*		mpGoldText;
	TextUI*		mpTimerText;


public:
	void SetLevelText(int level);
	void BuildSkillUI(vector<Skill*>& skills);
	void BuildGoldText();


public:
	void Init();
};

