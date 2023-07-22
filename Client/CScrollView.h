#pragma once
#include "CUI.h"

class CTexture;
class CPanelUI;
class CScrollBar;


class CScrollView :
    public CUI
{
private:
    CTexture*   mpTex; // ���۷� ����� �ؽ���
    CScrollBar* mpScrollBar; // ��ũ�� ��

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
