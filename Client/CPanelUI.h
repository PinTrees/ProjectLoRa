#pragma once
#include "CUI.h"


class CTexture;

class CPanelUI :
    public CUI
{
private:
    Vect2       mvDragStartPos;
    bool        mFixedPos;
    CTexture*   mpTex;


public:
    void SetFixedPos(bool active) { mFixedPos = active; }
    void SetTexture(CTexture* pTex) { mpTex = pTex; }
    CTexture* GetTexture() { return mpTex; }


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

