#pragma once
#include "CUI.h"



class CRow :
	public CUI
{
private:
	ALIGNMENT		mAlignment;			
	AXIS_ALIGNMENT  mMainAxisAligment;	// �ڽĵ��� ���Ĺ���� ���� [ ����, ����, ��� ], ������

	float			mSpacing;			// �ڽ� UI���� ���ݹ�ġ


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

