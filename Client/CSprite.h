#pragma once
#include "CRes.h"



class CSprite :
    public CRes
{
private:
    HDC         mDC;
    Image*      mImage;

    UINT mWidth;
    UINT mHeight;

public:
    void Load(const wstring& strFilePath);
    //void Create(UINT width, UINT hieght, COLORREF color = NULL);

    UINT Width() { return mWidth; }
    UINT Heigth() { return mHeight; }

    HDC GetDC() { return mDC; }

    Image* GetImage() { return mImage; }


public:
    void Render(HDC dc, Vect2 vPos, Vect2 vSize);


private:
    CSprite();
    virtual ~CSprite();

    friend class CResMgr;
};
