#pragma once
#include "CUI.h"



class CRow :
	public CUI
{
private:
	ALIGNMENT		mAlignment;			
	AXIS_ALIGNMENT  mMainAxisAligment;	// 자식들의 정렬방식을 결정 [ 좌측, 우측, 가운데 ], 개발중

	float			mSpacing;			// 자식 UI들의 간격배치


public:
	void SetAlignment(ALIGNMENT alignment) { mAlignment = alignment; }
	void SetSpacing(float spacing) { mSpacing = spacing; }


public:
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	virtual void MouseOn() override {};
	virtual void MouseLbtnDown() override {};
	virtual void MouseLbtnUp() override {};
	virtual void MouseLbtnClick() override {};

	CLONE(CRow);


public:
	CRow();
	virtual ~CRow() override;
};

