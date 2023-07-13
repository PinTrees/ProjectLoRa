#pragma once
#include "CRes.h"
class CFont :
    public CRes
{
private:
    HDC         mDC;
    HFONT       mDefaultFont;
<<<<<<< Updated upstream
    wstring     mStr;
=======
>>>>>>> Stashed changes

    COLORREF    mInnerColor;
    COLORREF    mOuterColor;

    bool        mBorder;

public:
    void Create(const wstring& _text);
    void SelectFont(int _size, const wstring& _name, bool _border);
    void DeleteFont(const wstring& _text);

<<<<<<< Updated upstream
    void PrintWord(Vec2 _vPos);

    void SetWord(const wstring& _str) { mStr = _str; }
    void SetInnerColor(COLORREF _color) { mInnerColor = _color; }
    void SetOuterColor(COLORREF _color) { mOuterColor = _color; }

=======
    void PrintWord(HDC dc, Vect2 _vPos, const wstring& str);

    void SetInnerColor(COLORREF _color) { mInnerColor = _color; }
    void SetOuterColor(COLORREF _color) { mOuterColor = _color; }

    void SetBorder(bool _border) { mBorder = _border; }
>>>>>>> Stashed changes

    HDC GetDC() { return mDC; }

private:
    CFont(HDC _mDC);
    virtual ~CFont();

    friend class CResMgr;
};

