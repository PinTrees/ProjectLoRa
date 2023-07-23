#pragma once
#include "CBtnUI.h"


class TileBtnUI :
	public CBtnUI
{
private:
	int             mIdx;

public:
	void SetIdx(int _idx) { mIdx = _idx; }


public:
	virtual void Render(HDC dc) override;

	virtual void MouseOn();
	virtual void MouseLbtnDown() override {}
	virtual void MouseLbtnUp() override {}
	virtual void MouseLbtnClick() override;

	CLONE(TileBtnUI);


public:
	TileBtnUI();
	virtual ~TileBtnUI();

};

