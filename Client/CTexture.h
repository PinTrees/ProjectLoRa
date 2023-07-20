#pragma once
#include "CRes.h"




class CTexture :
    public CRes
{
private:
    HDC         mDC;

    // Bitmap
    HBITMAP     mhBit;
    BITMAP      mBitInfo;


public:
    void Load(const wstring& strFilePath);
    void Create(UINT width, UINT hieght, COLORREF color = NULL);

    void Clear(COLORREF color);

    UINT Width() { return mBitInfo.bmWidth; }
    UINT Heigth () { return mBitInfo.bmHeight; }

    HDC GetDC() { return mDC; }

    HBITMAP GetHBitmap() { return mhBit; }


private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;
};

