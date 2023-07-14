#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* _focusedUI;
	bool isMouseOnUI;
public:
	void Update();

public:
	void SetFocusUI(CUI* ui);

	void SetIsMouseOn(bool _b) { isMouseOnUI = _b; }
	bool GetIsMouseOnUI() { return isMouseOnUI; }
public:
	CUI* GetTargetUI(CUI* parentUI);
	CUI* GetFocusUI();
};

