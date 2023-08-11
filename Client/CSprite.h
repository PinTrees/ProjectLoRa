#pragma once
#include "CRes.h"


enum class SPRITE_RENDER_TYPE
{
    NORMAL,     // Normal [png, jpg] Render
    POINT,      // Pixel Point Render
};


class CSprite :
    public CRes
{
private:
    HDC         mDC;
    Image*      mImage;

    // ÇÈ¼¿ ·»´õ¸µ ½Ã »ç¿ë
    HBITMAP     mhBit;

    SPRITE_RENDER_TYPE  mRenderType;

    UINT mWidth;
    UINT mHeight;


public:
    void SetRenderMode(SPRITE_RENDER_TYPE type) { mRenderType = type; }
    Image* GetImage() { return mImage; }


public:
    void Load(const wstring& strFilePath);
    //void Create(UINT width, UINT hieght, COLORREF color = NULL);

    UINT Width() { return mWidth; }
    UINT Heigth() { return mHeight; }

    HDC GetDC() { return mDC; }


public:
    void Render(HDC dc, Vect2 vPos, Vect2 vSize);


private:
    CSprite();
    virtual ~CSprite() override;

    friend class CResMgr;
};
