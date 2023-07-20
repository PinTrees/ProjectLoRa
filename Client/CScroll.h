#pragma once
#include "CUI.h"

class CTexture;
class CPanelUI;

class CScroll :
    public CUI
{
private:
    CTexture*       mpTex; // 버퍼로 사용할 텍스쳐
    CUI*            mpTargetUI; // 스크롤UI에 출력할 UI
    CPanelUI*       mpScrollBar; // 스크롤 바
    Vect2           mvInitScrollPos; // 스크롤 바의 초기위치

    float           mRatio;

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    CLONE(CScroll);

public:
    CScroll(CUI* _pUI, Vect2 _size);
    ~CScroll();
};

