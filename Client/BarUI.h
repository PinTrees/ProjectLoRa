#pragma once

#include "CUI.h"

class CObejct;

class BarUI :
    public CUI
{
private:
    float       mFillAmount;


public:
    void SetFillAmount(float amount) { mFillAmount = amount; };


public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void FinalUpdate() override;

    CLONE(BarUI);


public:
    BarUI();
    ~BarUI();

    friend class CObject;
};

