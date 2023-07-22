#pragma once
#include "CUI.h"

class CTexture;
class CPanelUI;
class CScrollBar;


class CScrollView :
    public CUI
{
private:
    CTexture*   mpTex; // 버퍼로 사용할 텍스쳐
    CScrollBar* mpScrollBar; // 스크롤 바

    Vect2       mvContentSize;
    float       mRatio;


public:
    void SetVerticalScroll();


public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void AddChild(CUI* ui) override;

    CLONE(CScrollView);


public:
    CScrollView();
    virtual ~CScrollView();
};
