#pragma once
#include "CUI.h"

class CTexture;
class CPanelUI;

class CScroll :
    public CUI
{
private:
    CTexture*       mpTex; // ���۷� ����� �ؽ���
    CUI*            mpTargetUI; // ��ũ��UI�� ����� UI
    CPanelUI*       mpScrollBar; // ��ũ�� ��
    Vect2           mvInitScrollPos; // ��ũ�� ���� �ʱ���ġ

    float           mRatio;

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    CLONE(CScroll);

public:
    CScroll(CUI* _pUI, Vect2 _size);
    ~CScroll();
};

