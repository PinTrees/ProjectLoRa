#pragma once
#include "CUI.h"


enum class AXIS
{
    HORIZONTAL,
    VERTICAL
};


class CScrollView;
class CTexture;


class CScrollBar :
	public CUI
{
private:
    AXIS            mAxis;
    CScrollView*    mScrollView;

    CTexture*       mpBufferTexture;

    Vect2           mvDragStartPos;
    bool            mbDrag;
    

public:
    void SetTexture(CTexture* pTex) { mpBufferTexture = pTex; }
    CTexture* GetTexture() { return mpBufferTexture; }


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
