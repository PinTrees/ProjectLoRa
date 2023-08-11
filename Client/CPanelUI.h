#pragma once
#include "CUI.h"


class CTexture;
class CSprite;

class CPanelUI :
    public CUI
{
private:
    Vect2       mvDragStartPos;

    bool        mFixedPos;

    bool        mFixedPos_x;
    bool        mFixedPos_y;

    CSprite*    mpTexture;



public:
    void SetFixedPos(bool active) { mFixedPos = active; }
    void SetFixedPosX(bool active_x) { mFixedPos_x = active_x; }
    void SetFixedPosY(bool active_y) { mFixedPos_y = active_y; }

    void SetTexture(CSprite* pTex) { mpTexture = pTex; }
    CSprite* GetTexture() { return mpTexture; }


public:
    virtual void Update();
    virtual void Render(HDC _dc) override;
    
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);


public:
    CPanelUI();
    virtual ~CPanelUI();
};

