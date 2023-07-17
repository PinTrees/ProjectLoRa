#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* _focusedUI;
	bool mbMouseOnUI;


public:
	void Update();


public:
	void SetFocusUI(CUI* ui);
	void SetMouseOn(bool _b) { mbMouseOnUI = _b; }
	bool IsMouseOn() { return mbMouseOnUI; }


public:
	CUI* GetTargetUI(CUI* parentUI);
	CUI* GetFocusUI();
};
