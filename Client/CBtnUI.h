#pragma once
#include "CUI.h"
class CBtnUI :
	public CUI
{

	typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

private:
	BTN_FUNC        mpFunc;
	DWORD_PTR mparam1;
	DWORD_PTR mparam2;
public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		mpFunc = _pFunc;
		mparam1 = _param1;
		mparam2 = _param2;
	}


	CLONE(CBtnUI);

public:
	CBtnUI();
	~CBtnUI();
};

