#pragma once
#include "CUI.h"
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
class CPanelUI :
    public CUI
{
private:
<<<<<<< Updated upstream
    Vec2    mvDragStartPos;

public:
    virtual void Update();
        virtual void Render(HDC _dc);
=======
    Vect2       mvDragStartPos;

public:
    virtual void Update();
    virtual void Render(HDC _dc);
>>>>>>> Stashed changes
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

