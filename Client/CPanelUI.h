#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
private:
    Vect2    mvDragStartPos;
    bool    mbFixedPos;
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

public:
    void SetFixedPos(bool _b) { mbFixedPos = _b; }
    bool isFixed() { return mbFixedPos; }



public:
    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

