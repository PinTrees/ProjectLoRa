#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC         mDC;
    HBITMAP     mhBit;
    BITMAP      mBitInfo;

public:
    void Load(const wstring& strFilePath);

    UINT Width() { return mBitInfo.bmWidth; }
    UINT Heigth () { return mBitInfo.bmHeight; }

    HDC GetDC() { return mDC; }
private:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};

