#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
private:
    Vect2       mvDragStartPos;

    bool        mFixedPos_x;
    bool        mFixedPos_y;


public:
    void SetFixedPos_x(bool active_x) { mFixedPos_x = active_x; }
    void SetFixedPos_y(bool active_y) { mFixedPos_y = active_y; }
    void SetFixedPos_xy(bool active) { mFixedPos_x = active; mFixedPos_y = active; }

    void SetDragStartPos(Vect2 _dragStart) { mvDragStartPos = _dragStart; }
    Vect2 GetDragStartPos() { return mvDragStartPos; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);
    
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);

public:
    CPanelUI();
    virtual ~CPanelUI() override;
};

