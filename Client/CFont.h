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
    void Create(const wstring& _text);
    void SelectFont(int _size, const wstring& _name, bool _border);
    void DeleteFont(const wstring& _text);

    void PrintWord(HDC dc, Vect2 _vPos, const wstring& str);

    void SetInnerColor(COLORREF _color) { mInnerColor = _color; }
    void SetOuterColor(COLORREF _color) { mOuterColor = _color; }


    HDC GetDC() { return mDC; }

private:
    CFont(HDC _mDC);
    virtual ~CFont();

    friend class CResMgr;
};

