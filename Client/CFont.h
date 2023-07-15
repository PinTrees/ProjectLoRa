#pragma once
#include "CRes.h"



class CFont :
    public CRes
{
private:
    HDC         mDC;
    HFONT       mDefaultFont;

    COLORREF    mInnerColor;
    COLORREF    mOuterColor;

    bool        mBorder;


public:
    void Load(const wstring& _text, const wstring& _name, int _size, bool _border);
    void Render(HDC dc, const wstring& str, Vect2 pos, Vect2 scale);

    void SetInnerColor(COLORREF _color) { mInnerColor = _color; }
    void SetOuterColor(COLORREF _color) { mOuterColor = _color; }

    HDC GetDC() { return mDC; }


private:
    CFont(HDC _mDC);
    virtual ~CFont();

    friend class CResMgr;
};

