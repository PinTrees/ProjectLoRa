#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
private:
    Vect2    mvDragStartPos;

public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

public:
    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

