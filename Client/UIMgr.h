#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* mFocusedUI;
	bool mbMouseOnUI;


public:
	void Update();


public:
	void SetTop(CUI* ui);
	void SetFocusUI(CUI* ui);

	void SetMouseOnUI(bool _b) { mbMouseOnUI = _b; }
	bool IsMouseOnUI() { return mbMouseOnUI; }


public:
	CUI* GetTargetUI(CUI* parentUI);
	CUI* GetFocusUI();
};
