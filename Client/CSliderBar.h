#pragma once
#include "CUI.h"


class CTexture;
class CSlider;

class CSliderBar :
	public CUI
{
private:
	CSlider*	mpOwner;
	CTexture*	mpTex;

	Vect2           mvDragStartPos;
	bool            mbDrag;


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;

	CLONE(CSliderBar);


public:
	CSliderBar();
	virtual ~CSliderBar();

	friend class CSlider;
};

