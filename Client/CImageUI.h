#pragma once
#include "CUI.h"


enum class IAMGE_FILLED_AXIS
{
	VERTICAL,
	HORIZONTAL,
};

enum class IMAGE_TYPE
{
	DEFAULT,
	FILLED
};



class CTexture;


class CImageUI :
	public CUI
{
private:
	CTexture* mpBufferTexture;
	CTexture* mDefaultTex;
	COLORREF  mColor;

	IMAGE_TYPE mUID;

	// Filled type value
	float	  mFilledAmount;
	IAMGE_FILLED_AXIS	mFilledAxis;
	RECT_DIRECTION		mFilledDirection;


public:
	void SetTexture(CTexture* tex) { mpBufferTexture = tex; };
	void SetColor(COLORREF color);


public:
	// Filled type Function 
	void SetImageType(IMAGE_TYPE type) { mUID = type; }
	void SetFilledAmount(float amount) { mFilledAmount = amount; }


public:
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CImageUI);


public:
	CImageUI();
	~CImageUI() override;
};

