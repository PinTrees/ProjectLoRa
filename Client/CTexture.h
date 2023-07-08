#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         mDC;
    HBITMAP     mhBit;
    BITMAP      mBitInfo;

    Vec2        mvSize;

public:
    void Load(const wstring& strFilePath);

    void CREATE(UINT width, UINT hieght, COLORREF color = NULL);

    UINT Width() { return mBitInfo.bmWidth; }
    UINT Heigth () { return mBitInfo.bmHeight; }

    HDC GetDC() { return mDC; }

    HBITMAP GetHBitmap() { return mhBit; }

    Vec2 GetSize() { return mvSize; }
    void SetSize(Vec2 _vSize) { mvSize = _vSize; }
private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;
};

