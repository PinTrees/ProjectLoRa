#pragma once
#include "CUI.h"

typedef void(*SLID_FUNC) (DWORD_PTR);

class CTexture;
class CSlider;

class CSliderBar :
	public CUI
{
private:
	CSlider*	mpOwner;
	CTexture*	mpTex;

	Vect2		mvDragStartPos;

	SLID_FUNC	mpFunc;
	DWORD_PTR	mParam;

public:
	void SetOwner(CSlider* owner) { mpOwner = owner; }
	void SetTexture(CTexture* pTex) { mpTex = pTex; }

public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;

	void SetFunc(SLID_FUNC func, DWORD_PTR param)
	{
		mpFunc = func;
		mParam = param;
	}

	CLONE(CSliderBar);


public:
	CSliderBar();
	virtual ~CSliderBar();
};

