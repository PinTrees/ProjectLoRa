#pragma once
#include "CUI.h"


class CTexture;
class CSlider;

class CSliderBar :
	public CUI
{
private:
	CSlider* mpOwner;
	CTexture* mpTex;


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;
	CLONE(CSliderBar);


public:
	CSliderBar();
	virtual ~CSliderBar();
};

