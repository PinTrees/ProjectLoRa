#pragma once
#include "CUI.h"

class CTexture;
class CPanelUI;
class CScrollBar;
class CImageUI;


class CScrollView :
    public CUI
{
private:
    CTexture*       mpBufferTexture;      // 버퍼로 사용할 텍스쳐
    CScrollBar*     mpScrollBar;          // 스크롤 바
    CImageUI*       mpScrollRoad;         // 스크롤 로드

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
