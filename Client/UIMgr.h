#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* _focusedUI;

public:
	void Update();

public:
	void SetFocusUI(CUI* ui);

public:
	CUI* GetTargetUI(CUI* parentUI);
	CUI* GetFocusUI();
};

