#pragma once
#include "CRes.h"

struct tTextStyle;

class CFont :
    public CRes
{
private:
    HFONT       mDefaultFont;
    wstring     mFullPath;

public:
    void Load(const wstring& _text, const wstring& _name, int _size);
    void Render(HDC dc, const wstring& str, Vect2 pos, Vect2 scale, const tTextStyle& style);


private:
    CFont(HDC _mDC);
    virtual ~CFont() override;

    friend class CResMgr;
};

