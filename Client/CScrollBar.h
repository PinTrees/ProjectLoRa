#pragma once
#include "CUI.h"


enum class AXIS
{
    HORIZONTAL,
    VERTICAL
};


class CScrollView;


class CScrollBar :
	public CUI
{
private:
    AXIS            mAxis;
    CScrollView*    mScrollView;
    Vect2           mvDragStartPos;
    bool            mbDrag;
    

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void MouseOn() override;
    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnUp() override;


    CLONE(CScrollBar);


public:
    CScrollBar();
    virtual ~CScrollBar();

    friend class CScrollView;
};
