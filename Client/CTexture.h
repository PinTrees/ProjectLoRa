#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         mDC;
    HBITMAP     mhBit;
    BITMAP      mBitInfo;

    Vec2        mvRelativeSize;

public:
    void Load(const wstring& strFilePath);

    void CREATE(UINT width, UINT hieght, COLORREF color = NULL);

    UINT Width() { return mBitInfo.bmWidth; }
    UINT Heigth () { return mBitInfo.bmHeight; }

    void SetSize(Vec2 _size) { mvRelativeSize = _size; }
    Vec2 GetSize() { return mvRelativeSize; }

    HDC GetDC() { return mDC; }

    HBITMAP GetHBitmap() { return mhBit; }
private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;
};

