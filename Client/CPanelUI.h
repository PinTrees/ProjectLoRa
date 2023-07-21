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
    CSprite*    mpSprite;


public:
    void SetFixedPos(bool active) { mFixedPos = active; }
    void SetTexture(CSprite* pTex) { mpSprite = pTex; }
    CSprite* GetTexture() { return mpSprite; }


public:
    virtual void Update();
    virtual void Render(HDC _dc) override;
    
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);


public:
    CPanelUI();
    virtual ~CPanelUI() override;
};

