#pragma once

class CTexture;
class CSprite;
class CFont;
class CSound;
class CRes;


class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CRes*> mMapSprite;
	map<wstring, CRes*> mMapTex;
	map<wstring, CRes*> mMapFont;
	map<wstring, CRes*> mMapSound;


public:
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);

	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

	CTexture* CreateTexture(const wstring& strkey, UINT width, UINT height, COLORREF color=NULL);

	CFont* LoadFont(const wstring& _strKey, const wstring& _strRelativePath, int _size);
	CFont* FindFont(const wstring& _strKey);

	CSprite* LoadSprite(const wstring& _strKey, const wstring& _strRelativePath);
	CSprite* FindSprite(const wstring& _strKey);

	friend class CObject;
};

